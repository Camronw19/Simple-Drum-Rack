/*
  ==============================================================================

    DrumCellContainer.h
    Created: 18 Mar 2023 1:26:41pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DrumCell.h"

//==============================================================================
/*
*/
class DrumCellContainer  : public juce::Component
{
public:
    DrumCellContainer(Simple_Drum_RackAudioProcessor&);
    ~DrumCellContainer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    const int mNUM_CELLS = 8; 
    std::vector<DrumCell> mDrumCells; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumCellContainer)
};
