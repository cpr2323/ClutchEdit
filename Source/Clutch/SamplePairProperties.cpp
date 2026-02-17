#include "SamplePairProperties.h"
#include "SampleProperties.h"

void SamplePairProperties::initValueTree ()
{
    SampleProperties openSampleProperties ({}, ValueTreeWrapper<SampleProperties>::WrapperType::owner, ValueTreeWrapper<SampleProperties>::EnableCallbacks::no);
    openSampleProperties.setType (SampleProperties::SampleType::open, false);
    getValueTree ().addChild (openSampleProperties.getValueTree (), -1, nullptr);

    SampleProperties closedSampleProperties ({}, ValueTreeWrapper<SampleProperties>::WrapperType::owner, ValueTreeWrapper<SampleProperties>::EnableCallbacks::no);
    closedSampleProperties.setType (SampleProperties::SampleType::closed, false);
    getValueTree ().addChild (closedSampleProperties.getValueTree (), -1, nullptr);
}

juce::ValueTree SamplePairProperties::getOpenSampleVT ()
{
    return getValueTree ().getChildWithProperty (SampleProperties::TypePropertyId, "open");
}

juce::ValueTree SamplePairProperties::getClosedSampleVT ()
{
    return getValueTree ().getChildWithProperty (SampleProperties::TypePropertyId, "closed");
}

