#include "media.h"

Media::Media(string path = "/dev/video0", uint16_t rate = 30, uint32_t resolution = 1080*720): 
			sDevPath(path), uRate(rate), uResolution(resolution){}
{
	iFd = open(sDevPath.c_str(),O_RDWR);
}

Media::~Media(void)
{
}

void Media::setDevPath(string &sPath)
{
	sDevPath = sPath;
}

string Media::getDevPath()
{
	return sDevPath;
}

size_t Media::readFrame(uint8_t *buf, size_t maxSize)
{

}

void Media::setFrameRate(uint16_t rate)
{

}

void Media::setFrameResolution(uint32_t resolution)
{

}

void Media::showMediaInfo()
{

}
