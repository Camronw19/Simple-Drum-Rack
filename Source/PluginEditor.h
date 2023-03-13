/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DrumCell.h"

//==============================================================================
/**
*/
class Simple_Drum_RackAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Simple_Drum_RackAudioProcessorEditor (Simple_Drum_RackAudioProcessor&);
    ~Simple_Drum_RackAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
 
    DrumCell mDC1;

    Simple_Drum_RackAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Simple_Drum_RackAudioProcessorEditor)
};
