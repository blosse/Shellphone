// Ye this is hopefully turning into a music player at some point
#include <iostream>
#include "src/parseInput.cpp"
#include "portaudio.h"
#include <sndfile.h>
using namespace std;

#define BUFFER_LEN 1024
#define MAX_CHANNELS 2

static int audioCallback(
    const void *inputBuffer,
    void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData) {
        SNDFILE *infile = (SNDFILE*)userData;
        float *out = (float*)outputBuffer;
        int framesRead = sf_readf_float(infile, out, framesPerBuffer);

        if (framesRead < framesPerBuffer) {
            return paComplete; //End of file
        }
        return paContinue;
    }

int main(int argc, char* argv[]) {

    cout << "Welcome to the show\n" << endl;

    if (!parseInput(argc, argv)) {
        return 1;
    }

    SF_INFO sfinfo;
    SNDFILE *infile;
    memset(&sfinfo, 0, sizeof(sfinfo));
    // Check for failure when opening the input file
    if (!(infile = sf_open(argv[1], SFM_READ, &sfinfo))) {
        cout << "Unable to open input file" << argv[1] << endl;
        puts(sf_strerror(NULL));
        return 1;
    }
    // Check for number of allowed channels
    if (sfinfo.channels > MAX_CHANNELS) {
        cout << "Unable to process more than " << MAX_CHANNELS << " channels" << endl;
        sf_close(infile);
        return 1;
    }
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        sf_close(infile);
        return 1;
    }

    //Here's a bunch of declarations for 'ya
    PaStream *stream;
    PaStreamParameters outputParams;
    outputParams.device = Pa_GetDefaultOutputDevice();
    outputParams.channelCount = sfinfo.channels;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &stream,
        NULL,
        &outputParams,
        sfinfo.samplerate,
        BUFFER_LEN,
        paClipOff,
        audioCallback,
        infile);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        Pa_Terminate();
        sf_close(infile);
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        sf_close(infile);
        return 1;
    }

    // Wait for stream to finish
    // TODO Maybe run stream in separate thread or something
    while (Pa_IsStreamActive(stream)) {
        Pa_Sleep(100);
    }

    Pa_CloseStream(stream);
    Pa_Terminate();
    sf_close(infile);

    cout << "Song is over! What now?" << endl;
    return 0;
}
