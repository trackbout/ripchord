#pragma once

#include "JuceHeader.h"
#include "System.h"

//==============================================================================
// A util class to load the images/icons used in this plugin as Drawables.
// We internally use a SharedResourcePointer to avoid dupplicating the drawables
// and reloading the files for each plugin instance.
class Images
{
public:
    //==============================================================================
    Images() = default;

    // Set images for a button with a single state
    void setDrawableButtonImages (DrawableButton& inButton, const String& inSvgFilename)
    {
        jassert (inSvgFilename.endsWithIgnoreCase (".svg"));

        if (auto* drawable = getDrawable (inSvgFilename))
        {
            inButton.setImages (drawable);
        }
    }

    // Set images for a button with a "down" state
    void setDrawableButtonImages (DrawableButton& inButton,
                                  const String& inNormalSvgFilename, const String& inOverSvgFilename,
                                  const String& inDownSvgFilename, const String& inDisabledSvgFilename)
    {
        inButton.setImages (getDrawable (inNormalSvgFilename), nullptr, // normal, over
                            getDrawable (inDownSvgFilename), nullptr, // down, disabled
                            nullptr, nullptr, nullptr, nullptr); // normalOn, overOn downOn, disabledOn
    }

    // Set images for a toggle button
    void setDrawableButtonImages (DrawableButton& inButton,
                                  const String& inNormalSvgFilename, const String& inOverSvgFilename,
                                  const String& inDownSvgFilename, const String& inDisabledSvgFilename,
                                  const String& inNormalOnSvgFilename, const String& inOverOnSvgFilename,
                                  const String& inDownOnSvgFilename, const String& inDisabledOnSvgFilename)
    {
        inButton.setImages (getDrawable (inNormalSvgFilename), nullptr, nullptr, nullptr,  // normal, over, down, disabled
                            getDrawable (inNormalOnSvgFilename), nullptr, nullptr, nullptr);  // normalOn, overOn, downOn, disabledOn
    }

    const Drawable* getDrawable (const String& inFilename)
    {
        return internalImages->getDrawable (inFilename);
    }

private:
    //==============================================================================
    class InternalImages
    {
    public:
        //==============================================================================
        InternalImages() {}

        const Drawable* getDrawable (const String& inFilename)
        {
            if (inFilename.isEmpty() || !inFilename.endsWithIgnoreCase (".svg"))
            {
                return nullptr;
            }

            int index = mFilenames.indexOf (inFilename, true);

            if (index >= 0)
            {
                return mDrawables[index];
            }

            return buildDrawable (inFilename);
        }

    private:
        //==============================================================================
        const Drawable* buildDrawable (const String& inFilename)
        {
            jassert (inFilename.endsWithIgnoreCase (".svg"));

            auto appDataPath = System::getDefaultUserDataPath (ProjectInfo::companyName, ProjectInfo::projectName);
            auto imagesPath = appDataPath.getChildFile ("Images");

            std::unique_ptr<Drawable> drawable = Drawable::createFromSVGFile (imagesPath.getChildFile (inFilename));

            if (drawable == nullptr)
            {
                auto fileNameWithoutPoint = inFilename.replace (".", "_");

                for (int j = 0; j < BinaryData::namedResourceListSize; ++j)
                {
                    if (String (BinaryData::namedResourceList[j]) == fileNameWithoutPoint)
                    {
                        int numBytes = 0;
                        auto ressource = BinaryData::getNamedResource (fileNameWithoutPoint.getCharPointer(), numBytes);
                        drawable = Drawable::createFromImageData (ressource, numBytes);
                        break;
                    }
                }
            }

            mDrawables.add (drawable.release());
            mFilenames.add (inFilename);
            return mDrawables.getLast();
        }

        //==============================================================================
        StringArray mFilenames;
        OwnedArray<Drawable> mDrawables;
    };

    // We use a SharedResourcePointer to avoid dupplicating the InternalImages.
    SharedResourcePointer<InternalImages> internalImages;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Images)
};
