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
    : AudioProcessorEditor (&p), audioProcessor (p), mDC1(p), mDC2(p)
{
    mDC1.setCellID("C1"); 
    mDC1.setMidiKey(1); 
    addAndMakeVisible(mDC1); 

    mDC2.setCellID("C2");
    mDC2.setMidiKey(2);
    addAndMakeVisible(mDC2);

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

    auto rCellBox = r.removeFromBottom(getHeight() / 2); 
    rCellBox.setLeft(20); 
    rCellBox.setRight(getWidth() - 20); 
    rCellBox.setBottom(getHeight() - 20); 

    auto rC1 = rCellBox.removeFromLeft(rCellBox.getWidth() / 2); 
    auto rC2 = rCellBox; 

    rC1.expand(-5, -5);
    rC2.expand(-5, -5);

    mDC1.setBounds(rC1);
    mDC2.setBounds(rC2);

}
