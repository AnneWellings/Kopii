/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CircularBufferAudioProcessor::CircularBufferAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	), tree(*this, nullptr)
#endif
{

	NormalisableRange<float> feedbackRange(0, .995, 0.005, .6);
	tree.createAndAddParameter("feedback", "Gain", "feedback", feedbackRange, 0.5f, nullptr, nullptr);

	NormalisableRange<float> delayRange(0, 1, 0, 1);
	tree.createAndAddParameter("delay1", "Delay 1", "delay1", delayRange, 1.0f, nullptr, nullptr);
	tree.createAndAddParameter("delay2", "Delay 2", "delay2", delayRange, 0.0f, nullptr, nullptr);
	tree.createAndAddParameter("delay3", "Delay 3", "delay3", delayRange, 0.0f, nullptr, nullptr);
	tree.createAndAddParameter("delay4", "Delay 4", "delay4", delayRange, 0.0f, nullptr, nullptr);
	tree.createAndAddParameter("delay5", "Delay 5", "delay5", delayRange, 0.0f, nullptr, nullptr);
	tree.createAndAddParameter("delay6", "Delay 6", "delay6", delayRange, 0.0f, nullptr, nullptr);
	tree.createAndAddParameter("delay7", "Delay 7", "delay7", delayRange, 0.0f, nullptr, nullptr);
	tree.createAndAddParameter("delay8", "Delay 8", "delay8", delayRange, 0.0f, nullptr, nullptr);

	tree.state = ValueTree("savedParams");
}

CircularBufferAudioProcessor::~CircularBufferAudioProcessor()
{
}

//==============================================================================
const String CircularBufferAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool CircularBufferAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool CircularBufferAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool CircularBufferAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double CircularBufferAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int CircularBufferAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int CircularBufferAudioProcessor::getCurrentProgram()
{
	return 0;
}

void CircularBufferAudioProcessor::setCurrentProgram(int index)
{
}

const String CircularBufferAudioProcessor::getProgramName(int index)
{
	return {};
}

void CircularBufferAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void CircularBufferAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	const int numInputChannels = getTotalNumInputChannels();
	const int delayBufferSize = 9 * (sampleRate + samplesPerBlock); //+samplesperblock is just a safety cushion of extra space
	mSampleRate = sampleRate;

	mDelayBuffer.setSize(numInputChannels, delayBufferSize);
	mDelayBuffer.clear(); //Added to stop feedback at vst startup
}

void CircularBufferAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CircularBufferAudioProcessor::isBusesLayoutSupported(const BusesLayout & layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

int measure = 0;

void CircularBufferAudioProcessor::processBlock(AudioBuffer<float> & buffer, MidiBuffer & midiMessages)
{
	//ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	playHead = this->getPlayHead();
	playHead->getCurrentPosition(currentPositionInfo);

	float bpm = currentPositionInfo.bpm;
	float timeSigNum = currentPositionInfo.timeSigNumerator;
	float timeSigDen = currentPositionInfo.timeSigDenominator;

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());


	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.

	const int bufferLength = buffer.getNumSamples();
	const int delayBufferLength = mDelayBuffer.getNumSamples();

	bool delay1 = (*tree.getRawParameterValue("delay1") == 1) ? true : false;
	bool delay2 = (*tree.getRawParameterValue("delay2") == 1) ? true : false;
	bool delay3 = (*tree.getRawParameterValue("delay3") == 1) ? true : false;
	bool delay4 = (*tree.getRawParameterValue("delay4") == 1) ? true : false;
	bool delay5 = (*tree.getRawParameterValue("delay5") == 1) ? true : false;
	bool delay6 = (*tree.getRawParameterValue("delay6") == 1) ? true : false;
	bool delay7 = (*tree.getRawParameterValue("delay7") == 1) ? true : false;
	bool delay8 = (*tree.getRawParameterValue("delay8") == 1) ? true : false;

	measure = delay2 * timeSigNum;
	float delayTime = ((60 / bpm) * 1000) / 2;

	//if ((int)timeSigNum % 4 == 0)
	//{
		//delayTime = delayTime / 2;
	//}

	float delayTime2 = delayTime * 2;
	float delayTime3 = delayTime2 + delayTime;
	float delayTime4 = delayTime2 * 2;
	float delayTime5 = delayTime4 + delayTime;
	float delayTime6 = delayTime4 + delayTime2;
	float delayTime7 = delayTime4 + delayTime3;
	float measureTime = delayTime2 * timeSigNum;
	//float delayTime3 = delayTime2 + delayTime;

	//pow(10,(gainSlider.getValue()/20));
	float feedback = *tree.getRawParameterValue("feedback");

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		const float* bufferData = buffer.getReadPointer(channel);
		const float* delayBufferData = mDelayBuffer.getReadPointer(channel);

		fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData, feedback);

		//getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime, feedback*feedback);

		if (delay2)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTime, feedback);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime + delayTime, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 2) + delayTime, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 3) + delayTime, feedback * .25);
		}
		if (delay3)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTime2, feedback);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime + delayTime2, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 2) + delayTime2, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 3) + delayTime2, feedback * .25);
		}
		if (delay4)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTime3, feedback);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime + delayTime3, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 2) + delayTime3, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 3) + delayTime3, feedback * .25);
		}
		if (delay5)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTime4, feedback);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime + delayTime4, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 2) + delayTime4, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 3) + delayTime4, feedback * .25);
		}
		if (delay6)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTime5, feedback);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime + delayTime5, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 2) + delayTime5, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 3) + delayTime5, feedback * .25);
		}
		if (delay7 && (int)timeSigNum % 4 == 0)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTime6, feedback);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime + delayTime6, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 2) + delayTime6, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 3) + delayTime6, feedback * .25);
		}
		if (delay8 && (int)timeSigNum % 4 == 0)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, delayTime7, feedback);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime + delayTime7, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 2) + delayTime7, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, (measureTime * 3) + delayTime7, feedback * .25);
		}
		if (delay1)
		{
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime, feedback * .75);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime * 2, feedback * .5);
			getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData, measureTime * 3, feedback * .25);
		}

	}

	mWritePosition += bufferLength;
	mWritePosition %= delayBufferLength; //modulo wraps it around when it reaches the end (ex: 11%10=1)
}

void CircularBufferAudioProcessor::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength,
	const float* bufferData, const float* delayBufferData, float feedback)
{
	//copy data from main buffer to delay buffer
	if (delayBufferLength > bufferLength + mWritePosition)
	{
		mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, feedback, feedback);
	}
	else //make it wrap
	{
		const int bufferRemaining = delayBufferLength - mWritePosition;

		mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, feedback, feedback);
		mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, feedback, feedback);
	}
}

void CircularBufferAudioProcessor::getFromDelayBuffer(AudioBuffer<float> & buffer, int channel, const int bufferLength,
	const int delayBufferLength, const float* bufferData, const float* delayBufferData, float delayTime, float feedback)
{
	//int delayTime = 500; //milliseconds
	//int delayTime = *tree.getRawParameterValue("time");

	const int readPosition = static_cast<int>(delayBufferLength + mWritePosition - (mSampleRate * delayTime / 1000)) % delayBufferLength;

	if (delayBufferLength > bufferLength + readPosition)
	{
		buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferLength, feedback);
	}
	else
	{
		const int bufferRemaining = delayBufferLength - readPosition;
		buffer.addFrom(channel, 0, delayBufferData + readPosition, bufferRemaining, feedback);
		buffer.addFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining, feedback);
	}
}



//==============================================================================
bool CircularBufferAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CircularBufferAudioProcessor::createEditor()
{
	return new CircularBufferAudioProcessorEditor(*this);
}

//==============================================================================
void CircularBufferAudioProcessor::getStateInformation(MemoryBlock & destData)
{
	ScopedPointer<XmlElement> xml(tree.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void CircularBufferAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	ScopedPointer <XmlElement> theParams(getXmlFromBinary(data, sizeInBytes));

	if (theParams != nullptr)
	{
		if (theParams->hasTagName(tree.state.getType()))
		{
			tree.state = ValueTree::fromXml(*theParams);
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new CircularBufferAudioProcessor();
}