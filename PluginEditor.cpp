/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CircularBufferAudioProcessorEditor::CircularBufferAudioProcessorEditor(CircularBufferAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p), feedbackLabel("", "Gain:")
{


	//feedbackAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "feedback", feedbackSlider);
	attachments.add(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "feedback", feedbackSlider));

	feedbackSlider.setSliderStyle(Slider::Rotary);
	//feedbackSlider.addListener(this);
	feedbackSlider.setRange(0.0, 0.995, 0.005);
	feedbackSlider.setLookAndFeel(&circSliderLook);
	addAndMakeVisible(&feedbackSlider);

	playHead = processor.getPlayHead();
	if (playHead != nullptr)
	{
		playHead->getCurrentPosition(currentPositionInfo);
		timeSigNum = currentPositionInfo.timeSigNumerator;
	}

	resized();

	//bool delay1 = (*processor.tree.getRawParameterValue("delay1") == 1) ? true : false;

	feedbackLabel.attachToComponent(&feedbackSlider, false);

	buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay1", delayButton1));
	delayButton1.setLookAndFeel(&circSliderLook);
	addAndMakeVisible(&delayButton1);

	buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay2", delayButton2));
	delayButton2.setLookAndFeel(&circSliderLook);
	addAndMakeVisible(&delayButton2);

	buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay3", delayButton3));
	delayButton3.setLookAndFeel(&circSliderLook);
	addAndMakeVisible(&delayButton3);

	buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay4", delayButton4));
	delayButton4.setLookAndFeel(&circSliderLook);
	addAndMakeVisible(&delayButton4);

	buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay5", delayButton5));
	delayButton5.setLookAndFeel(&circSliderLook);
	addAndMakeVisible(&delayButton5);

	buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay6", delayButton6));
	delayButton6.setLookAndFeel(&circSliderLook);
	addAndMakeVisible(&delayButton6);

	if (timeSigNum == 4)
	{
		buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay7", delayButton7));
		delayButton7.setLookAndFeel(&circSliderLook);
		addAndMakeVisible(&delayButton7);

		buttonAttachments.add(new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "delay8", delayButton8));
		delayButton8.setLookAndFeel(&circSliderLook);
		addAndMakeVisible(&delayButton8);
	}

	//feedbackAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getValueTreeState(), CircularBufferAudioProcessor::paramFeedback, *feedbackSlider);
}

void CircularBufferAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &feedbackSlider)
	{
		///processor.rawVolume = pow(10, (feedbackSlider.getValue() / 20));
	}
}

CircularBufferAudioProcessorEditor::~CircularBufferAudioProcessorEditor()
{
	feedbackSlider.removeListener(this);
	attachments.remove(0);
}

//==============================================================================
void CircularBufferAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::black);
}

void CircularBufferAudioProcessorEditor::resized()
{
	if ((int)timeSigNum % 3 == 0)
	{
		setSize(300, 100);
		feedbackSlider.setBounds(140, 50, 150, 40);
		delayButton1.setBounds(20, 20, 40, 40);
		delayButton2.setBounds(60, 20, 40, 40);
		delayButton3.setBounds(100, 20, 40, 40);
		delayButton4.setBounds(20, 60, 40, 40);
		delayButton5.setBounds(60, 60, 40, 40);
		delayButton6.setBounds(100, 60, 40, 40);
	}
	else
	{
		setSize(350, 100);
		feedbackSlider.setBounds(200, 50, 150, 40);
		delayButton1.setBounds(20, 20, 40, 40);
		delayButton2.setBounds(60, 20, 40, 40);
		delayButton3.setBounds(100, 20, 40, 40);
		delayButton4.setBounds(140, 20, 40, 40);
		delayButton5.setBounds(20, 60, 40, 40);
		delayButton6.setBounds(60, 60, 40, 40);
		delayButton7.setBounds(100, 60, 40, 40);
		delayButton8.setBounds(140, 60, 40, 40);
	}
}



