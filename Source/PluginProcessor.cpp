/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CascadePlugin2AudioProcessor::CascadePlugin2AudioProcessor()
//changed
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    mainProcessor(new juce::AudioProcessorGraph()),
    muteInput(new juce::AudioParameterBool("mute", "Mute Input", false)),
    processorSlot1(new juce::AudioParameterChoice("slot1", "Slot 1", processorChoices, 0)),
    processorSlot2(new juce::AudioParameterChoice("slot2", "Slot 2", processorChoices, 0)),
    processorSlot3(new juce::AudioParameterChoice("slot3", "Slot 3", processorChoices, 0)),
    bypassSlot1(new juce::AudioParameterBool("bypass1", "Bypass 1", false)),
    bypassSlot2(new juce::AudioParameterBool("bypass2", "Bypass 2", false)),
    bypassSlot3(new juce::AudioParameterBool("bypass3", "Bypass 3", false)),
    testparam(new juce::AudioParameterFloat("test", "testParam", 0.0f, 22000.0f, 1000.0f)),//add
    paramQ(new juce::AudioParameterFloat("Q", "paramQ", 0.0f,20.0f, 1.0f)),
    first_update(1)
{
    addParameter(muteInput);

    addParameter(processorSlot1);
    addParameter(processorSlot2);
    addParameter(processorSlot3);

    addParameter(bypassSlot1);
    addParameter(bypassSlot2);
    addParameter(bypassSlot3);

    //add
    addParameter(testparam);
    addParameter(paramQ);
}

CascadePlugin2AudioProcessor::~CascadePlugin2AudioProcessor()
{
}

//==============================================================================
const juce::String CascadePlugin2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CascadePlugin2AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool CascadePlugin2AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool CascadePlugin2AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double CascadePlugin2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CascadePlugin2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CascadePlugin2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void CascadePlugin2AudioProcessor::setCurrentProgram(int index)
{
}

const juce::String CascadePlugin2AudioProcessor::getProgramName(int index)
{
    return {};
}

void CascadePlugin2AudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
//changed
void CascadePlugin2AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(),
        getMainBusNumOutputChannels(),
        sampleRate, samplesPerBlock);

    mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);

    initialiseGraph();
}

//changed
void CascadePlugin2AudioProcessor::releaseResources()
{
    mainProcessor->releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
//changed
bool CascadePlugin2AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

//changed
void CascadePlugin2AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    updateGraph();

    mainProcessor->processBlock(buffer, midiMessages);
}

//==============================================================================
bool CascadePlugin2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CascadePlugin2AudioProcessor::createEditor()
{
    return new CascadePlugin2AudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void CascadePlugin2AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CascadePlugin2AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CascadePlugin2AudioProcessor();
}
