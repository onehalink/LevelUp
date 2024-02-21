#include "Bitmap.h"



namespace Engine
{
	Bitmap::Bitmap()
	{
		Memory::Clear( this, sizeof(Bitmap) );
	}

	Bitmap::Bitmap(SizeType width, SizeType height, Format format)
	{
		SizeType channelCount	= format == Format::B8G8R8 ? 3 : 4;
		SizeType imageSize		= width * height * channelCount;


		this->buffer		= Allocator::Allocate<Byte>(imageSize);
		this->width			= width;
		this->height		= height;
		this->format		= format;
		this->channelCount	= channelCount;
	}

	Bitmap::Bitmap(const Bitmap& other)
	{
		CopyFrom(other);
	}

	Bitmap::Bitmap(Bitmap&& other)
	{
		buffer			= other.buffer;
		width			= other.width;
		height			= other.height;
		format			= other.format;
		channelCount	= other.channelCount;

		other.buffer = nullptr;
	}

	Bitmap::~Bitmap()
	{
		Allocator::Release( reinterpret_cast<Byte*>(buffer) );
	}

	Void Bitmap::SetPixel(SizeType x, SizeType y, UInt32 pixel)
	{
		Memory::Copy(
			&pixel,
			reinterpret_cast<Byte*>(buffer) + ( width * y + x ) * channelCount,
			channelCount
		);
	}

	UInt32 Bitmap::GetPixel(SizeType x, SizeType y) const
	{
		UInt32 ret;
		Memory::Copy(
			reinterpret_cast<Byte*>(buffer) + ( width * y + x ) * channelCount,
			&ret,
			channelCount
		);

		return ret;
	}

	Void Bitmap::FlipHorizontal()
	{
		SizeType halfWidth = width / 2;
		for ( SizeType y = 0; y < height; y++ )
			for ( SizeType x = 0; x < halfWidth; x++ )
				for ( SizeType index = 0; index < channelCount; index++ )
					Swap(
						reinterpret_cast<Byte*>(buffer) + ( width * y + x					) * channelCount + index,
						reinterpret_cast<Byte*>(buffer) + ( width * y + ( width - 1 - x )	) * channelCount + index
					);
	}

	Void Bitmap::FlipVertical()
	{
		SizeType halfHeight = height / 2;
		for ( SizeType y = 0; y < halfHeight; y++ )
			for ( SizeType x = 0; x < width; x++ )
				for ( SizeType index = 0; index < channelCount; index++ )
					Swap(
						reinterpret_cast<Byte*>(buffer) + ( width * y					+ x	) * channelCount + index,
						reinterpret_cast<Byte*>(buffer) + ( width * ( height - 1 - y )	+ x	) * channelCount + index
					);
	}

	Bool Bitmap::IsValid(const Void* buffer, SizeType byteCount)
	{
		if ( byteCount < DefaultBitsOffset )
			return false;

		if ( !Memory::Equal(buffer, "BM", 2) )
			return false;

		{
			auto descriptor = reinterpret_cast<const InfoHeader*>( reinterpret_cast<const Byte*>(buffer) + FileHeaderSize );
			if (
				descriptor->bitCount != 24 &&
				descriptor->bitCount != 32
				)
				return false;
		}
		
		return true;
	}

	Bitmap Bitmap::Decode(const Void* buffer, SizeType byteCount)
	{
		auto descriptor = reinterpret_cast<const InfoHeader*>( reinterpret_cast<const Byte*>(buffer) + FileHeaderSize );

		
		Bitmap ret( descriptor->width, descriptor->height, descriptor->bitCount == 24 ? Format::B8G8R8 : Format::B8G8R8A8 );
		Memory::Copy(
			reinterpret_cast<const Byte*>(buffer) + reinterpret_cast<const FileHeader*>(buffer)->offset,
			ret.GetBuffer(),
			descriptor->imageSize
		);

		return ret;
	}

	HeapMemory Bitmap::Encode(const Bitmap& instance)
	{
		SizeType imageSize = instance.width * instance.height * instance.channelCount;
		

		SizeType tatolSize = DefaultBitsOffset + imageSize;
		HeapMemory ret(tatolSize);
		{
			auto buffer = ret.GetBuffer();

			Memory::Clear(
				buffer,
				DefaultBitsOffset
			);
			Memory::Copy(
				instance.buffer,
				reinterpret_cast<Byte*>(buffer) + DefaultBitsOffset,
				imageSize
			);

			// set FileHeader
			{
				auto descriptor			= reinterpret_cast<FileHeader*>(buffer);
				descriptor->magic[0]	= 'B';
				descriptor->magic[1]	= 'M';
				descriptor->size		= tatolSize;
				descriptor->offset		= DefaultBitsOffset;
			}

			// set InfoHeader
			{
				auto descriptor			= reinterpret_cast<InfoHeader*>( reinterpret_cast<Byte*>(buffer) + FileHeaderSize );
				descriptor->size		= InfoHeaderSize;
				descriptor->width		= instance.width;
				descriptor->height		= instance.height;
				descriptor->planes		= 1;
				descriptor->bitCount	= instance.channelCount * 8;
				descriptor->imageSize	= imageSize;
			}
		}

		return ret;
	}

	Void* Bitmap::GetBuffer()
	{
		return buffer;
	}

	const Void* Bitmap::GetBuffer() const
	{
		return buffer;
	}

	SizeType Bitmap::GetWidth() const
	{
		return width;
	}

	SizeType Bitmap::GetHeight() const
	{
		return height;
	}

	Bitmap::Format Bitmap::GetFormat() const
	{
		return format;
	}

	SizeType Bitmap::GetChannelCount() const
	{
		return channelCount;
	}

	Bitmap& Bitmap::operator=(const Bitmap& other)
	{
		this->~Bitmap();
		CopyFrom(other);

		return *this;
	}

	Bitmap& Bitmap::operator=(Bitmap&& other)
	{
		Swap( &buffer,			&other.buffer		);
		Swap( &width,			&other.width		);
		Swap( &height,			&other.height		);
		Swap( &format,			&other.format		);
		Swap( &channelCount,	&other.channelCount	);

		return *this;
	}

	Void Bitmap::CopyFrom(const Bitmap& instance)
	{
		SizeType imageSize = instance.width * instance.height * instance.channelCount;


		buffer			= Allocator::Allocate<Byte>(imageSize);
		width			= instance.width;
		height			= instance.height;
		format			= instance.format;
		channelCount	= instance.channelCount;

		Memory::Copy(
			instance.buffer,
			buffer,
			imageSize
		);
	}
}