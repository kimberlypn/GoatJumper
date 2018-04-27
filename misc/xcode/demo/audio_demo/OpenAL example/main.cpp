//
//  main.cpp
//  OpenAL example
//
//  Created by Jason Fiammetta on 2/23/18.
//  Copyright (c) 2018 Jason Fiammetta. All rights reserved.
//

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

int main(int argc, const char * argv[]) {
    
    ALCdevice *dev;
    ALCcontext *ctx;
    
    struct stat statbuf ;
    
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <audiofile>\n", argv[0]);
        return 0;
    }
    
    dev = alcOpenDevice(NULL);
    if(!dev)
    {
        fprintf(stderr, "alcOpenDevice not working.\n");
        return 1;
    }
    
    ctx = alcCreateContext(dev, NULL);
    alcMakeContextCurrent(ctx);
    if(!ctx)
    {
        fprintf(stderr, "alcCreateContext not working.\n");
        return 1;
    }
    
    {
        
#define NUM_BUFFERS 3
#define BUFFER_SIZE 4096
        
        ALuint source;
        ALuint buffers[NUM_BUFFERS];
        ALuint frequency;
        ALenum format;
        
        char *buf;      //unsigned?
        
        int pid;
        int files[2];
        FILE * f;
        
        alGenBuffers(NUM_BUFFERS, buffers);
        alGenSources(1, &source);
        
        if(alGetError() != AL_NO_ERROR)
        {
            fprintf(stderr, "Error generating :(\n");
            return 1;
        }
        
        if(stat(argv[1], &statbuf) != 0 || !S_ISREG(statbuf.st_mode))
        {
            fprintf(stderr, "%s doesn't seem to be a regular file :(\n", argv[1]);
            return 1;
        }
        
        if(pipe(files) != 0) {
            fprintf(stderr, "Pipe failed :(\n");
            return 1;
        }
        
        pid = fork();
        
        switch(pid) {
            case -1:
                fprintf(stderr, "Fork failed");
                return 1;
                break;
                
            case 0:
                close(STDOUT_FILENO);
                dup2(files[1], STDOUT_FILENO);
                
                execlp("mplayer", "-nogui", "-really-quiet", "-novideo",
                       "-noconsolecontrols", "-ao", "pcm:file=/dev/stdout",
                       argv[1], (char*)NULL);
                _exit(1);
                
            default:
                close(files[1]);
                break;
        }
        
        f = fdopen(files[0], "rb");
        
        
        buf = (char*) malloc(BUFFER_SIZE);      //(unsigned char*) ??
        //fprintf(stderr, "%d\n", buf[0]);
        fread(buf, 1, 12, f);
        //fprintf(stderr, "%d\n", buf[0]);
        fprintf(stderr, "%d\n", buf[10]);
        //fprintf(stderr, "%d\n", buf[11]);
        fread(buf, 1, 8, f);
        if(buf[0] != 'f' || buf[1] != 'm' || buf[2] != 't' || buf[3] != ' ') {
            fprintf(stderr, "%d\n", buf[0]);
            fprintf(stderr, "%d\n", buf[1]);
            fprintf(stderr, "%d\n", buf[2]);
            fprintf(stderr, "Not 'fmt ' :(\n");

            fclose(f);
            return 1;
        }
        
        {
            int channels;
            int bits;
            
            fread(buf, 1, 2, f);
            if(buf[0] != 1 || buf[1] != 0)
            {
                fprintf(stderr, "Not PCM :(\n");
                fclose(f);
                return 1;
            }
            
            fread(buf, 1, 2, f);
            channels  = buf[1]<<8;
            channels |= buf[0];
            
            fread(buf, 1, 4, f);
            frequency  = buf[3]<<24;
            frequency |= buf[2]<16;
            frequency |= buf[1]<8;
            frequency |= buf[0];
            
            //ignore
            fread(buf, 1, 6, f);
            
            fread(buf, 1, 2, f);
            bits  = buf[1]<<8;
            bits |= buf[0];

            format = 0;
            if(bits == 8)
            {
                if(channels == 1)
                    format = AL_FORMAT_MONO8;
                else if(channels == 2)
                    format = AL_FORMAT_STEREO8;
            }
            else if(bits == 16)
            {
                if(channels == 1)
                    format = AL_FORMAT_MONO16;
                else if(channels == 2)
                    format = AL_FORMAT_STEREO16;
            }
            if(!format)
            {
                fprintf(stderr, "Incompatible format (%d, %d) :(\n", channels, bits);
                fclose(f);
                return 1;
            }
        }
        
        fread(buf, 1, 8, f);
        if(buf[0] != 'd' || buf[1] != 'a' || buf[2] != 't' || buf[3] != 'a')
        {
            fclose(f);
            fprintf(stderr, "Not 'data' :(\n");
            return 1;
        }
        
        {
            int ret;
            ret = fread(buf, 1, BUFFER_SIZE, f);
            alBufferData(buffers[0], format, buf, ret, frequency);
            
            ret = fread(buf, 1, BUFFER_SIZE, f);
            alBufferData(buffers[1], format, buf, ret, frequency);
            ret = fread(buf, 1, BUFFER_SIZE, f);
            alBufferData(buffers[2], format, buf, ret, frequency);
            if(alGetError() != AL_NO_ERROR)
            {
                fprintf(stderr, "Error loading :(\n");
                return 1;
            }
            
            //start playback
            alSourceQueueBuffers(source, NUM_BUFFERS, buffers);
            alSourcePlay(source);
            if(alGetError() != AL_NO_ERROR)
            {
                fprintf(stderr, "Error starting :(\n");
                return 1;
            }

            while (!feof(f))
            {
                ALuint buffer;
                ALint val;
                
                alGetSourcei(source, AL_BUFFERS_PROCESSED, &val);
                if(val <= 0) { continue; }
                
                while (val--) {
                    ret = fread(buf, 1, BUFFER_SIZE, f);
                    
                    alSourceUnqueueBuffers(source, 1, &buffer);
                    alBufferData(buffer, format, buf, ret, frequency);
                    alSourceQueueBuffers(source, 1, &buffer);
                    if(alGetError() != AL_NO_ERROR)
                    {
                        fprintf(stderr, "Error buffering :(\n");
                        return 1;
                    }
                    
                    alGetSourcei(source, AL_SOURCE_STATE, &val);
                    if(val != AL_PLAYING)
                    {
                        alSourcePlay(source);
                    }
                }
            }
            
            fclose(f);
            free(buf);
            
            {
                ALint val;
                do {
                    alGetSourcei(source, AL_SOURCE_STATE, &val);
                } while(val == AL_PLAYING);
            }
            
            alDeleteSources(1, &source);
            alDeleteBuffers(NUM_BUFFERS, buffers);
        }
        
    }
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
    
    return 0;
}
