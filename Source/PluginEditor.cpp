/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CascadePlugin2AudioProcessorEditor::CascadePlugin2AudioProcessorEditor (CascadePlugin2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //コンボボックスの初期設定★
    slot1.addItem("Empty", 1);
    slot1.addItem("Oscillator", 2);
    slot1.addItem("Gain", 3);
    slot1.addItem("Filter", 4);
    slot1.setSelectedId(1);
    addAndMakeVisible(&slot1);//コンボボックスの可視化です。
    slot1.addListener(this);//リスナー関数に紐づけます。

    setSize (400, 300);
}

CascadePlugin2AudioProcessorEditor::~CascadePlugin2AudioProcessorEditor()
{
}

//==============================================================================
void CascadePlugin2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void CascadePlugin2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    slot1.setBounds(40, 30, 200, 30);
}

//★comboBox listener function
void CascadePlugin2AudioProcessorEditor::comboBoxChanged(juce::ComboBox* combo1)
{
    audioProcessor.setSlot1(slot1.getSelectedId() - 1);//processorSlot1の値を変更します。★
}