/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class PluginLook : public LookAndFeel_V4
{
public:
	PluginLook()
	{
	}

	void TextEditor::LookAndFeelMethods::drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& theEditor)
	{
		g.setColour(Colours::coral);
		Rectangle<float> tempRect(width, height);
		g.drawRoundedRectangle(tempRect, 8.0f, 4.0f);
	}

	void Label::LookAndFeelMethods::drawLabel(Graphics& g, Label& theLabel)
	{
		g.setColour(Colours::white);
		if (theLabel.isMouseOver())
		{
			g.setColour(Colours::grey);
		}
		if (theLabel.isMouseButtonDown())
		{
			g.setColour(Colours::darkgrey);
		}
		//Rectangle<int> tempRect = theLabel.getLocalBounds();
		Rectangle<float>tempRect2(theLabel.getX(), theLabel.getY() - (theLabel.getHeight() / 2), theLabel.getWidth(), theLabel.getHeight());
		g.drawRoundedRectangle(tempRect2, 8.0f, 4.0f);
		g.drawText(theLabel.getText(), tempRect2, Justification::centred, true);
	}


	void Button::LookAndFeelMethods::drawTickBox(Graphics & g, Component & component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
	{
		g.setColour(Colours::white);
		Rectangle<float> tempRect(x, y, w, h);
		if (isMouseOverButton)
		{
			g.setColour(Colours::grey);
		}
		if (isButtonDown)
		{
			g.setColour(Colours::darkgrey);
		}
		g.drawRoundedRectangle(tempRect, 2.0f, 4.0f);
		if (ticked)
		{
			g.setColour(Colours::coral);
			if (component.isMouseOver())
			{
				g.setColour(Colours::lightcoral);
			}
			if (component.isMouseButtonDown())
			{
				g.setColour(Colours::white);
			}
			Path p;
			/*Point<float> yourPoint(x+(w/2), y+(w/2));
			p.addStar(yourPoint, 5, w*.15, w*.55, 0.0f);*/
			Point<float> pointA(x - w, y + (h * .15));
			Point<float> pointB(x + (w / 2), y + h);
			Line<float> aLine(pointA, pointB);
			p.addLineSegment(aLine, 4.0f);
			Point<float> pointC(x + (w * .85), y - (h / 2));
			Line<float> bLine(pointB, pointC);
			p.addLineSegment(bLine, 4.0f);
			g.fillPath(p);
		}
	}


	void drawRotarySlider(Graphics & g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider & slider) override
	{
		const float radius = jmin(width / 2, height / 2) - 4.0f;
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		const float rw = radius * 2.0f;
		const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);


		// fill
		/*g.setColour(Colours::transparentBlack);
		g.fillEllipse(rx, ry, rw, rw);*/
		// outline

		g.setColour(Colours::white);
		if (slider.isMouseOver())
		{
			g.setColour(Colours::grey);
		}
		if (slider.isMouseButtonDown())
		{
			g.setColour(Colours::darkgrey);
		}
		g.drawEllipse(rx, ry, rw, rw, 4.0f);

		Path p;
		const float pointerLength = radius * 1.0f;
		const float pointerThickness = 4.0f;
		//Line<float> templine(centreX,centreY,centreX+radius,centreY+radius);
		//p.addArrow(templine,radius*1.0f, 4.0f,radius*1.0f);
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

		// pointer
		g.setColour(Colours::coral);
		if (slider.isMouseOver())
		{
			g.setColour(Colours::lightcoral);
		}
		if (slider.isMouseButtonDown())
		{
			g.setColour(Colours::white);
		}
		g.fillPath(p);
	}

}; // PLUGINLOOK_H_INCLUDED


   //==============================================================================
   /**
   */
class CircularBufferAudioProcessorEditor : public AudioProcessorEditor,
	public Slider::Listener
{
public:
	CircularBufferAudioProcessorEditor(CircularBufferAudioProcessor&);
	~CircularBufferAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	void sliderValueChanged(Slider* slider) override;
	//void buttonClicked(Button*button)override;
	//void textEditorTextChanged(TextEditor&);

	//ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
	OwnedArray<AudioProcessorValueTreeState::SliderAttachment> attachments;
	OwnedArray<AudioProcessorValueTreeState::ButtonAttachment> buttonAttachments;

private:
	PluginLook circSliderLook;
	PluginLook toggleButtonLook;

	AudioPlayHead* playHead;
	AudioPlayHead::CurrentPositionInfo currentPositionInfo;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	CircularBufferAudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CircularBufferAudioProcessorEditor)

		//ScopedPointer<Slider> feedbackSlider;
		Slider feedbackSlider;
	Label feedbackLabel;
	ToggleButton delayButton1, delayButton2, delayButton3, delayButton4, delayButton5, delayButton6, delayButton7, delayButton8;
	float timeSigNum = 4;

	//ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
};

#endif // PLUGINEDITOR_H_INCLUDED