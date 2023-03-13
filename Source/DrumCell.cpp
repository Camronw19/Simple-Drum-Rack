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
    mCellID.setText("", juce::dontSendNotification); 
    addAndMakeVisible(mCellID);

    mFileName.setText("Empty cell", juce::dontSendNotification); 
    mFileName.setJustificationType(juce::Justification::right); 
    addAndMakeVisible(mFileName); 

}

DrumCell::~DrumCell()
{
}

void DrumCell::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    juce::Rectangle<float> window;
    window.setBounds(0, 0, getWidth(), getHeight());
    g.drawRoundedRectangle(window, 6, 2);


}

void DrumCell::resized()
{
    auto r = getLocalBounds(); 

    auto rInfo = r.removeFromTop(20); 
    auto rID = rInfo.removeFromLeft(getWidth() / 4); 
    auto rfileName = rInfo.removeFromRight(getWidth() - 5); 

    mCellID.setBounds(rID); 
    mFileName.setBounds(rfileName); 

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
            mFileName.setText(myFile->getFileNameWithoutExtension(), juce::dontSendNotification);

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

void DrumCell::setCellID(juce::String ID)
{
    mCellID.setText(ID, juce::dontSendNotification);
}