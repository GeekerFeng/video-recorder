#include "media.h"

Media::Media(string path = "/dev/video0", uint16_t rate = 30, uint32_t resolution = 1080*720): 
			sDevPath(path), uRate(rate), uResolution(resolution){}
{
	
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
	fd_set fds;

	FD_ZERO(&fds);
	FD_SET(iFd, &fds);
	int r = select(iFd+1,&fds, NULL, NULL, NULL);
	if(-1 == r)
	{
		return -1;
	}
	
	if(-1 == xioctl(iFd, VIDIOC_DQBUF, &buf))
	{
		return -1;
	}
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

int Media::open(void)
{

}

int Media::close(void)
{
	struct v4l2_capability caps = {0};
	struct v4l2_format fmt = {0};
	struct v4l2_requestbuffers req = {0};
	struct v4l2_buffer buf = {0};

	iFd = open(sDevPath.c_str(),O_RDWR);
	if(iFd == -1)
	{
		return -1;
	}

	if(-1 == xioctl(iFd, VIDIOC_QUERYCAP, &caps))
	{
		return -1;
	}

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = uResWight;
	fmt.fmt.pix.height = uResHeight;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	fmt.fmt.pox.field = V4L2_FIELD_NONE;

	if(-1 == xioctl(iFd, VIDIOC_S_FMT, &fmt))
	{
		return -1;
	}

	req.count = 1;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	
	if(-1 == xioctl(iFd, VIDIOC_REQBUFS, &req))
	{
		return -1;
	}

	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	buf.index = 0;

	buffer = mmap(NULL,buf.length, RPOT_READ | PROT_WRITE, MAP_SHARED, iFd, buf.m.offset);

	if(-1 == xioctl(iFd, VIDIOC_STREAMON, &buf.type))
	{
		return -1;
	}
}
