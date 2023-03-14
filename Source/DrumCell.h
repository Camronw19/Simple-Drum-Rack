/*
  ==============================================================================

    DrumCell.h
    Created: 13 Mar 2023 3:18:44pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class DrumCell  : public juce::Component,
                  public juce::FileDragAndDropTarget
{
public:
    DrumCell(Simple_Drum_RackAudioProcessor& p);
    ~DrumCell() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void filesDropped(const juce::StringArray& files, int x, int y) override;
    bool isInterestedInFileDrag(const juce::StringArray& files) override;

    void setCellID(juce::String ID);
    void setMidiKey(int midiKey);

private:
    juce::Label mCellID;
    juce::Label mFileName;
    int mMidiKey; 


    Simple_Drum_RackAudioProcessor& audioProcessor; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumCell)
};
