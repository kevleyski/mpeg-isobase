#include <bitstream/omftag.h>
#include <mpeg-isobase/box/padding_bits.h>


namespace mpeg {
namespace isobase {


void PaddingBitsBox::parse_payload(Remainder left_payload) {
    Parsed::Entries entries{*this, parser(), left_payload, [](const auto &box) -> uint32_t { return box.sample_count; }};
    for(auto entry : entries) {
        parser().notify_about_header(entry);
    }
}

void PaddingBitsBox::output_fields(bitstream::output::meta::field::Stream &stream_) const {
    FullBox::output_fields(stream_);
    using namespace bitstream::output::meta::field::tag;
    using bitstream::output::meta::field::tag::Stream;
    const auto &stream = Stream(stream_);
    stream.tag(sample_count)  << "sample_count";
}


void PaddingBitsBox::Entry::output_fields(bitstream::output::meta::field::Stream &stream_) const {
    using namespace bitstream::output::meta::field::tag;
    using bitstream::output::meta::field::tag::Stream;
    const auto &stream = Stream(stream_);
    stream.tag(reserved1) << "reserved";
    stream.tag(pad1) << "pad1";
    stream.tag(reserved2) << "reserved";
    stream.tag(pad2) << "pad2";
}


}} // namespace mpeg::isobase

