/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IIRFilterAudioProcessorEditor::IIRFilterAudioProcessorEditor (IIRFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (400, 300);
    setupSlider(cutoffSlider, "Cutoff", cutoffLabel, 20.f, 20000.f, 440.f);
    setupSlider(resonanceSlider, "Resonance", resonanceLabel, 1.f, 10.f, 1.f);

    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.getAudioParameters(), "CUTOFF", cutoffSlider);
    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.getAudioParameters(), "RESONANCE", cutoffSlider);
}

IIRFilterAudioProcessorEditor::~IIRFilterAudioProcessorEditor()
{
}

//==============================================================================
void IIRFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void IIRFilterAudioProcessorEditor::resized()
{
    auto bound = getLocalBounds();

    cutoffSlider.setBounds(bound.removeFromLeft(getWidth()/2));
    resonanceSlider.setBounds(bound);
}

void IIRFilterAudioProcessorEditor::setupSlider(juce::Slider& slider, const std::string& name, juce::Label& label, float min, float max, float initValue)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    slider.setRange(min, max);
    slider.setValue(initValue);
    label.setSize(50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
}