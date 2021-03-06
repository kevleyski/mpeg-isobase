#include <bitstream/omftag.h>
#include <mpeg-isobase/box/chunk_large_offset.h>


namespace mpeg {
namespace isobase {


void ChunkLargeOffsetBox::parse_payload(Remainder left_payload) {
    Parsed::Entries entries{*this, parser(), left_payload};
    for(auto entry : entries) {
        parser().notify_about_header(entry);
    }
}

void ChunkLargeOffsetBox::output_fields(bitstream::output::meta::field::Stream &stream_) const {
    FullBox::output_fields(stream_);
    using namespace bitstream::output::meta::field::tag;
    using bitstream::output::meta::field::tag::Stream;
    const auto &stream = Stream(stream_);
    stream.tag(entry_count)  << "entry_count";
}


void ChunkLargeOffsetBox::Entry::output_fields(bitstream::output::meta::field::Stream &stream_) const {
    using namespace bitstream::output::meta::field::tag;
    using bitstream::output::meta::field::tag::Stream;
    const auto &stream = Stream(stream_);
    stream.tag(chunk_offset) << "chunk_offset";
}

}} // namespace mpeg::isobase

