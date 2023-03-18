/*
  ==============================================================================

    DrumCellContainer.cpp
    Created: 18 Mar 2023 1:26:41pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DrumCellContainer.h"

//==============================================================================
DrumCellContainer::DrumCellContainer(Simple_Drum_RackAudioProcessor& p)
{
   for (int i =0; i < mNUM_CELLS; i++)
   {
       mDrumCells.emplace_back(DrumCell(p)); 
       mDrumCells[i].setMidiKey(i); 
       mDrumCells[i].setCellID("C" + std::to_string(i)); 
       addAndMakeVisible(mDrumCells[i]); 
   }

}

DrumCellContainer::~DrumCellContainer()
{
}

void DrumCellContainer::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void DrumCellContainer::resized()
{
    auto r = getLocalBounds(); 
    std::vector<juce::Rectangle<int>> cellBounds; 

    auto row1 = r.removeFromTop(getHeight() / 2); 
    auto row2 = r; 
    juce::Rectangle<int> rx; 

    for (int i = 0; i < mNUM_CELLS; i++)
    {
        if (i <= 4)
        {
            rx = row1.removeFromLeft(r.getWidth() / 4); 
            mDrumCells[i].setBounds(rx);
        }
        else
        {
            rx = row2.removeFromLeft(r.getWidth() / 4);
            mDrumCells[i].setBounds(rx); 
        }
    }
    

}
