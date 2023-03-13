/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
//testing 

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Simple_Drum_RackAudioProcessorEditor::Simple_Drum_RackAudioProcessorEditor (Simple_Drum_RackAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //textbox
    addAndMakeVisible(testButton); 
    testButton.setButtonText("testing"); 
    //=========


    setSize (400, 300);
}

Simple_Drum_RackAudioProcessorEditor::~Simple_Drum_RackAudioProcessorEditor()
{
}

//==============================================================================
void Simple_Drum_RackAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Simple_Drum_RackAudioProcessorEditor::resized()
{
    auto r = getBounds(); 

    testButton.setBounds(r.removeFromBottom(50)); 
}
