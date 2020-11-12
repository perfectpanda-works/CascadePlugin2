/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CascadePlugin2AudioProcessorEditor  : public juce::AudioProcessorEditor,
    private juce::ComboBox::Listener
{
public:
    CascadePlugin2AudioProcessorEditor (CascadePlugin2AudioProcessor&);
    ~CascadePlugin2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void comboBoxChanged(juce::ComboBox* combo1) override;//Åö[2]add
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CascadePlugin2AudioProcessor& audioProcessor;

    juce::ComboBox slot1;//Åö[3]

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CascadePlugin2AudioProcessorEditor)
};
