/*
  ==============================================================================

    DrumCell.cpp
    Created: 13 Mar 2023 3:18:44pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DrumCell.h"

//==============================================================================
DrumCell::DrumCell(Simple_Drum_RackAudioProcessor& p)
    : audioProcessor(p)
{
    

}

DrumCell::~DrumCell()
{
}

void DrumCell::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText (mFileName, getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DrumCell::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

//======================

void DrumCell::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {
            //get the file name to print
            auto myFile = std::make_unique<juce::File>(file); 
            mFileName = myFile->getFileNameWithoutExtension();

            //load this file 
            audioProcessor.loadFile(file);
            repaint();
        }
    }
}

bool DrumCell::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }
    return false;
}