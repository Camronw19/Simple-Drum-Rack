/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
//testing Liam

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Simple_Drum_RackAudioProcessorEditor::Simple_Drum_RackAudioProcessorEditor (Simple_Drum_RackAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mDC1(p)
{
    mDC1.setCellID("C1"); 
    addAndMakeVisible(mDC1); 

    setSize (600, 400);
}

Simple_Drum_RackAudioProcessorEditor::~Simple_Drum_RackAudioProcessorEditor()
{
}

//==============================================================================
void Simple_Drum_RackAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void Simple_Drum_RackAudioProcessorEditor::resized()
{
    auto r = getBounds(); 

    mDC1.setBounds(50, 50, 200, 50); 

}
