/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Simple_Drum_RackAudioProcessor::Simple_Drum_RackAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    //registers basic audio formats (mp3, wav, etc.) so that you can stream audio
    mFormatManager.registerBasicFormats(); 

    //adds voices to the synthesizer based on const num declared in header file. 
    for (int i = 0; i < mNumVoices; i++)
    {
        mSampler.addVoice(new juce::SamplerVoice);
    }

    //sets ADSR Parameters 
    mADSRParameters.attack = 0.0;
    mADSRParameters.decay = 0.0;
    mADSRParameters.sustain = 5.0; 
    mADSRParameters.release = 1.0; 


}

Simple_Drum_RackAudioProcessor::~Simple_Drum_RackAudioProcessor()
{
}

//==============================================================================
const juce::String Simple_Drum_RackAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Simple_Drum_RackAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Simple_Drum_RackAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Simple_Drum_RackAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Simple_Drum_RackAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Simple_Drum_RackAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Simple_Drum_RackAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Simple_Drum_RackAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Simple_Drum_RackAudioProcessor::getProgramName (int index)
{
    return {};
}

void Simple_Drum_RackAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Simple_Drum_RackAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mSampler.setCurrentPlaybackSampleRate(sampleRate);
}

void Simple_Drum_RackAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Simple_Drum_RackAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Simple_Drum_RackAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::MidiMessage m;
    juce::MidiBuffer::Iterator it{ midiMessages };
    int sample;

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool Simple_Drum_RackAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Simple_Drum_RackAudioProcessor::createEditor()
{
    return new Simple_Drum_RackAudioProcessorEditor (*this);
}

//==============================================================================
void Simple_Drum_RackAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Simple_Drum_RackAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Simple_Drum_RackAudioProcessor();
}


void Simple_Drum_RackAudioProcessor::loadFile(const juce::String& path, int midiKey)
{
    juce::File file = juce::File(path); 
    mFormatReader = mFormatManager.createReaderFor(file); 
    
    juce::BigInteger note = midiKey; 
    juce::SamplerSound* newSound = new juce::SamplerSound("Sample", *mFormatReader, note, 0, 0.0, 0.0, 10.0); 

    auto newSource = std::make_unique<juce::AudioFormatReaderSource>(mFormatReader, true); 
    double lengthInSeconds = static_cast<double> (newSource->getTotalLength()) / mFormatReader->sampleRate;

    mADSRParameters.decay = lengthInSeconds; 
    newSound->setEnvelopeParameters(mADSRParameters); 
    mSampler.addSound(newSound);
}
