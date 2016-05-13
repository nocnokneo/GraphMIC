#pragma once

#include "gmLogicItkBinaryFunctorImageFilter.hpp"

#include <itkAndImageFilter.h>

namespace gm
{
    namespace Logic
    {
        namespace Itk
        {
            class AndImageFilter : public BinaryFunctorImageFilter
            {
            public:
                struct ID
                {
                    static constexpr auto input1 = "input 1";
                    static constexpr auto input2 = "input 2";
                    static constexpr auto output = "output";
                };
                
                static Register<AndImageFilter> Register;
                
                using Access = Enable::ImageTypes <
                    Enable::Dimension<2,3>,
                    Enable::Scalar<unsigned char, unsigned short, unsigned int, char, short, int>
                >;

                AndImageFilter() : BinaryFunctorImageFilter("AndImageFilter")
                {
                    log_trace(Log::New, this);
                    
                    this->add(new Slot::Input<Data::Image>(ID::input1, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Input<Data::Image>(ID::input2, Access::MakeConstraints(), Data::Required));
                    this->add(new Slot::Output<Data::Image>(ID::output, Access::MakeConstraints()));
                }
                
                template <class TImage>
                auto process() -> void
                {
                    using ImageType     = typename TImage::itk_image_t;
                    using FilterType    = itk::AndImageFilter<ImageType, ImageType>;
                    
                    auto filter         = FilterType::New();
                    auto output         = this->getOutput<Data::Image>(ID::output);
                    
                    BinaryFunctorImageFilter::applyParameters<FilterType>(filter);
                    
                    for (auto it : this->inputIterator())
                    {
                        filter->SetInput1(Image::ToItk<ImageType>(it.image(0)));
                        filter->SetInput2(Image::ToItk<ImageType>(it.image(1)));
                        filter->Update();
                        output->addImage(Image::FromItk<ImageType>(filter->GetOutput()));
                    }
                }
                
                auto run() -> void override
                {
                    log_trace(Log::Func);
                    
                    Invoke(this);
                }
            };
        }
    }
}
