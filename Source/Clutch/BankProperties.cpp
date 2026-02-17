#include "BankProperties.h"
#include "SamplePairProperties.h"
#include "SampleProperties.h"

void BankProperties::initValueTree ()
{
    for (auto samplePairIndex { 0 }; samplePairIndex < 16; ++samplePairIndex)
    {
        SamplePairProperties samplePairProperties ({}, ValueTreeWrapper<SamplePairProperties>::WrapperType::owner, ValueTreeWrapper<SamplePairProperties>::EnableCallbacks::no);
        SampleProperties openSampleProperties (samplePairProperties.getOpenSampleVT (), ValueTreeWrapper<SampleProperties>::WrapperType::owner, ValueTreeWrapper<SampleProperties>::EnableCallbacks::no);
        openSampleProperties.setFilename (juce::String (samplePairIndex + 1).paddedLeft ('0', 2) + "OH", false);
        SampleProperties closedSampleProperties (samplePairProperties.getClosedSampleVT (), ValueTreeWrapper<SampleProperties>::WrapperType::owner, ValueTreeWrapper<SampleProperties>::EnableCallbacks::no);
        closedSampleProperties.setFilename (juce::String (samplePairIndex + 1).paddedLeft ('0', 2) + "CH", false);
        getValueTree ().addChild (samplePairProperties.getValueTree (), -1, nullptr);
    }
}

void BankProperties::setName (juce::String name, bool includeSelfCallback)
{
    setValue (name, NamePropertyId, includeSelfCallback);
}

juce::String BankProperties::getName ()
{
    return getValue<juce::String> (NamePropertyId);
}

void BankProperties::forEachSamplePair (std::function<bool (juce::ValueTree samplePairVT, int samplePairIndex)> samplePairVTCallback)
{
    jassert (samplePairVTCallback != nullptr);
    auto curSamplePairIndex { 0 };
    ValueTreeHelpers::forEachChildOfType (data, SamplePairProperties::SamplePairTypeId, [this, &curSamplePairIndex, samplePairVTCallback] (juce::ValueTree samplePairVT)
    {
        auto keepIterating { samplePairVTCallback (samplePairVT, curSamplePairIndex) };
        ++curSamplePairIndex;
        return keepIterating;
    });

}

void BankProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (vt != data)
        return;

    if (property == NamePropertyId)
    {
        if (onNameChange)
            onNameChange (getName ());
    }
}
