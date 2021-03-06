/*************************************************************************
 *   > File Name: camera.c
 *   > Author: he.yang
 *   > Mail: yanghe9012@126.com
 *   > Created Time: 2014年10月14日 星期二 12时06分08秒
 *************************************************************************/

#include "camera.h"
#include "draw.h"
#include "font.h"

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
unsigned short *frameBuffer = 0;
unsigned short stride;

unsigned int scale = 1;

unsigned long buffer_count;
unsigned int win_x,win_y,win_xx,win_yy,win_w,win_h;
unsigned long width, height;
int  mclk = 24;

//pthread_mutex_t mut;

static char dev_name[20] = "/dev/video100";
static io_method io = IO_METHOD_MMAP;
static int fd = -1;
struct buffer_t buffers[32];
static unsigned int n_buffers = 0; 

#if 0
static void screen_clear()
{
	unsigned short *dst_clear = (unsigned short *)frameBuffer;
    int line;
    for(line = 0;line < 800; ++line)
    {
        memset(dst_clear,0,finfo.line_length);
        dst_clear += stride;
    }
}
#endif
#if 0
static void *show_pitcure(void *p)
{
    //pthread_mutex_lock(&mut);
    //printf("thread2:number = %d\n",number);
    //number++;
    //pthread_mutex_unlock(&mut);
    stride = finfo.line_length / 2;
	unsigned short *dst = (unsigned short *)frameBuffer + (win_xx + win_yy * stride);
	unsigned short *p_src;
	p_src = (unsigned short *)p;
	int line;
    pthread_mutex_lock(&mut);
	for (line = 0; line < height; ++line) {
		memcpy(dst,p_src,width*2);
		p_src += width;
		dst += stride;
	}
    pthread_mutex_unlock(&mut);
    return NULL;
}
static void *draw()
{
    pthread_mutex_lock(&mut);
	drawRect (200, 300, 100, 100, 0xffff0000);
	draw_shang (100, 200, 0xffff0000);
	draw_hai (120, 200, 0xffff0000);
	draw_hua (140, 200, 0xffff0000);
	draw_li (160, 200, 0xffff0000);
	draw_chuang (180, 200, 0xffff0000);
	draw_tong (200, 200, 0xffff0000);
	draw_yang (140, 240, 0xffff0000);
	draw_he (160, 240, 0xffff0000);

	draw_0 (100, 100, 0xffffffff);
	draw_1 (120, 100, 0xffffffff);
	draw_2 (140, 100, 0xffffffff);
	draw_3 (160, 100, 0xffffffff);
	draw_4 (180, 100, 0xffffffff);
	draw_5 (200, 100, 0xffffffff);
	draw_6 (220, 100, 0xffffffff);
	draw_7 (240, 100, 0xffffffff);
	draw_8 (260, 100, 0xffffffff);
	draw_9 (280, 100, 0xffffffff);

	draw0 (20, 10, 40, 40, 0xffff0000);
	draw1 (80, 10, 40, 40, 0xffff0000);
	draw2 (140, 10, 40, 40, 0xffff0000);
	draw3 (200, 10, 40, 40, 0xffff0000);
	draw4 (260, 10, 40, 40, 0xffff0000);
	draw5 (320, 10, 40, 40, 0xffff0000);
	draw6 (380, 10, 40, 40, 0xffff0000);
	draw7 (440, 10, 40, 40, 0xffff0000);
	draw8 (500, 10, 40, 40, 0xffff0000);
	draw9 (560, 10, 40, 40, 0xffff0000);
    pthread_mutex_unlock(&mut);
    return NULL;
}
static void process_image(void *p)
{
    pthread_mutex_init(&mut,NULL);
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,show_pitcure,p);
    pthread_create(&tid2,NULL,draw,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
}
#endif
#if 1
static void process_image(void *p)
{
    stride = finfo.line_length / 2;
    const char *str_uu = "上海华力创通半导体有限公司";
    Font font;
	unsigned short *dst = (unsigned short *)frameBuffer + (win_xx + win_yy * stride);
	unsigned short *p_src;
	unsigned short *p_font;
	p_src = (unsigned short *)p;
	p_font = (unsigned short *)p;
	int line;
    show_font(str_uu, &font, 50, 200, 0xffff0000,p_font);
    //pthread_mutex_lock(&mut);
	for (line = 0; line < height; ++line) {
		memcpy(dst,p_src,width*2);
		p_src += width;
		dst += stride;
	}
    //show_font(str_uu, &font, 50, 200, 0xffff0000);
    #if 0
	drawRect (200, 300, 100, 100, 0xffff0000);
	draw_shang (100, 200, 0xffff0000);
	draw_hai (120, 200, 0xffff0000);
	draw_hua (140, 200, 0xffff0000);
	draw_li (160, 200, 0xffff0000);
	draw_chuang (180, 200, 0xffff0000);
	draw_tong (200, 200, 0xffff0000);
	draw_yang (140, 240, 0xffff0000);
	draw_he (160, 240, 0xffff0000);

	draw_0 (100, 100, 0xffffffff);
	draw_1 (120, 100, 0xffffffff);
	draw_2 (140, 100, 0xffffffff);
	draw_3 (160, 100, 0xffffffff);
	draw_4 (180, 100, 0xffffffff);
	draw_5 (200, 100, 0xffffffff);
	draw_6 (220, 100, 0xffffffff);
	draw_7 (240, 100, 0xffffffff);
	draw_8 (260, 100, 0xffffffff);
	draw_9 (280, 100, 0xffffffff);

	draw0 (20, 10, 40, 40, 0xffff0000);
	draw1 (80, 10, 40, 40, 0xffff0000);
	draw2 (140, 10, 40, 40, 0xffff0000);
	draw3 (200, 10, 40, 40, 0xffff0000);
	draw4 (260, 10, 40, 40, 0xffff0000);
	draw5 (320, 10, 40, 40, 0xffff0000);
	draw6 (380, 10, 40, 40, 0xffff0000);
	draw7 (440, 10, 40, 40, 0xffff0000);
	draw8 (500, 10, 40, 40, 0xffff0000);
	draw9 (560, 10, 40, 40, 0xffff0000);
    #endif
}
#endif
#if 0
static void process_image(void *p)
{
	draw_shang (100, 200, 0xffff0000);
	draw_hai (120, 200, 0xffff0000);
	draw_hua (140, 200, 0xffff0000);
	draw_li (160, 200, 0xffff0000);
	draw_chuang (180, 200, 0xffff0000);
	draw_tong (200, 200, 0xffff0000);
	draw_yang (140, 240, 0xffff0000);
	draw_he (160, 240, 0xffff0000);
    #if 0
    char *str = "上海华力创通半导体有限公司";
    Font font;
    show_font(str, &font, 50, 50, 0xffff0000); 
    #endif
}
#endif
static int read_frame(void)
{
	struct v4l2_buffer buf;
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)){
		switch (errno){
			case -EAGAIN:
				return 0;
			case -EIO:
				/* Could ignore EIO, see spec. */
				/* fall through */
			default:
				errno_exit("VIDIOC_DQBUF");
		}
	}
	assert(buf.index < n_buffers);
	process_image(buffers[buf.index].start);
	if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
		errno_exit("VIDIOC_QBUF");
	return 1;
}

static void mainloop(void)
{  
	int frame_count = 0; 
	fd_set fds;
	struct timeval tv;
	int r;

	while(1){
		for (;;){
			/*TODO : comment: if the next paragram between #if 1 and #endif does not work, then
			 * the test pattern will always ended when calling VIDIOC_DQBUF iocontrol, although sometimes
			 * it can work for several hours. On the ohterwise, if the next paragram between #if 1 
			 * and #endif works, and if the  process_image function does not write image data to a
			 * file, then the test pattern can always being working rightly, but if writing data to a 
			 * file, then it can cause an usr_irq fault, maybe it's caused by the nfs, which needs to 
			 * verify latter. The next paragram before read_frame function is mainly used to call poll
			 * function*/

			FD_ZERO(&fds);
			FD_SET(fd, &fds);
			/* Timeout. */
			tv.tv_sec = 20;
			tv.tv_usec = 0;
			r = select(fd + 1, &fds, NULL, NULL, &tv);
			if (-1 == r){
				if (EINTR == errno) {
					printf("main loop : EINTR == errno!\n");
					continue;
				}
				errno_exit("select");
			}
			if (0 == r){
				fprintf(stderr, "select timeout\n");
				exit(EXIT_FAILURE);
			}
			if (read_frame()){
				frame_count++;
				break;
			}
		}
	}
} 
static void start_capturing(void)
{
	unsigned int i;
	enum v4l2_buf_type type;

	fprintf(stderr, "start_capturing\n");
	switch (io){
		case IO_METHOD_READ:
			/* Nothing to do. */    
			fprintf(stderr, "IO_METHOD_READ\n");
			break;
		case IO_METHOD_MMAP:
			fprintf(stderr, "IO_METHOD_MMAP\n");
			for (i = 0;i < n_buffers;++i){
				struct v4l2_buffer buf;
				CLEAR(buf);
				buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
				buf.memory = V4L2_MEMORY_MMAP;
				buf.index = i;
				if (-1 == xioctl(fd, VIDIOC_QBUF, &buf)) {
					errno_exit("VIDIOC_QBUF");
				}
			}
			type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

			if (-1 == xioctl(fd, VIDIOC_STREAMON, &type)) {
				errno_exit("VIDIOC_STREAMON");
			}
			break;
		case IO_METHOD_USERPTR:
			fprintf(stderr, "IO_METHOD_USERPTR");
			for (i = 0;i < n_buffers;++i){
				struct v4l2_buffer buf;
				CLEAR(buf);
				buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
				buf.memory = V4L2_MEMORY_USERPTR;
				buf.index = i;
				buf.m.userptr = (unsigned long) buffers[i].start;
				buf.length = buffers[i].length;
				if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
					errno_exit("VIDIOC_QBUF");
			}
			type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
				errno_exit("VIDIOC_STREAMON");
			break;
	}
}

static void init_read(unsigned int buffer_size)
{
	fprintf(stderr, "init_read\n");

	buffers[0].length = buffer_size;
	buffers[0].start = malloc(buffer_size);
	if (!buffers[0].start){
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
}

static void init_mmap(void)
{
	struct v4l2_requestbuffers req;
	CLEAR(req); 

	fprintf(stderr, "init_mmap\n");

	req.count = buffer_count;///4;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)){
		if (EINVAL == errno){
			fprintf(stderr, "%s does not support "
					"memory mapping\n", dev_name);
			exit(EXIT_FAILURE);
		}else{
			errno_exit("VIDIOC_REQBUFS");
		}
	}

	for (n_buffers = 0;n_buffers < req.count;++n_buffers){
		struct v4l2_buffer buf;
		CLEAR(buf);
		printf("n_buffers value :%d\n",n_buffers);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;
		if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
			errno_exit("VIDIOC_QUERYBUF");
		buffers[n_buffers].length = buf.length*scale;
		buffers[n_buffers].start = mmap(NULL /* start anywhere */,
				buf.length*scale,
				PROT_READ | PROT_WRITE /* required */,
				MAP_SHARED /* recommended */,
				fd,
				buf.m.offset);
		fprintf(stderr,
				"buffers[%d].start=0x%x,length=0x%x\n",
				n_buffers,
				(unsigned int )buffers[n_buffers].start,
				buf.length*scale);
		if (MAP_FAILED == buffers[n_buffers].start)
			errno_exit("mmap");
	}
}

static void init_device(void)
{
	struct v4l2_capability cap;
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_format fmt;
	unsigned int min;
	fprintf(stderr, "init_device\n");
	if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)){
		if (EINVAL == errno){
			fprintf(stderr, "%s is no V4L2 device\n", dev_name);
			exit(EXIT_FAILURE);
		}else{
			errno_exit("VIDIOC_QUERYCAP");
		}
	}
	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
		fprintf(stderr, "%s is no video capture device\n", dev_name);
		exit(EXIT_FAILURE);
	}

	/* Select video input, video standard and tune here. */
	CLEAR(cropcap);
	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)){
		crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		crop.c.left = win_x; 
		crop.c.top = win_y; 
		crop.c.width = win_w; 
		crop.c.height = win_h; 

		if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)){
			switch (errno){
				case -EINVAL:
					/* Cropping not supported. */
					break;
				default:
					/* Errors ignored. */
					break;
			}
		}
	}
	
	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	//fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV420;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB565;
	fmt.fmt.pix.field =   /*V4L2_FIELD_INTERLACED*/V4L2_FIELD_ANY;
	fmt.fmt.pix.priv = mclk;
	if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt)){
		errno_exit("VIDIOC_S_FMT");
	}
	/* Note VIDIOC_S_FMT may change width and height. */
	/* Buggy driver paranoia. */
	min = fmt.fmt.pix.width * 2;
	if (fmt.fmt.pix.bytesperline < min){
		fmt.fmt.pix.bytesperline = min;
	}
	min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
	if (fmt.fmt.pix.sizeimage < min){
		fmt.fmt.pix.sizeimage = min;
	}
	switch (io){
		case IO_METHOD_READ:
			fprintf(stderr, "IO_METHOD_READ\n");
			init_read(fmt.fmt.pix.sizeimage);
			break;
		case IO_METHOD_MMAP:
			fprintf(stderr, "IO_METHOD_MMAP\n");
			init_mmap();
			break;
		case IO_METHOD_USERPTR:
			fprintf(stderr, "IO_METHOD_USERPTR*******222\n");
			break;
	}
}
static void close_device(void)
{
	fprintf(stderr, "close_device\n");
	if (-1 == close(fd)){
		return;
	}
	fd = -1;
}

static void open_device(void)
{
	fprintf(stderr, "open_device\n");

	fd = open(dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);
	if (-1 == fd){
		printf("open video100 err\n");
		exit(EXIT_FAILURE);
	}
}

static void stop_capturing(void)
{
	enum v4l2_buf_type type;
	fprintf(stderr, "stop_capturing\n");
	switch (io){
		case IO_METHOD_READ:
			/* Nothing to do. */
			break;

		case IO_METHOD_MMAP:
		case IO_METHOD_USERPTR:
			type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
				errno_exit("VIDIOC_STREAMOFF");
			break;
	}
}

static void uninit_device(void)
{
	unsigned int i;
	fprintf(stderr, "uninit_device\n");
	switch (io){
		case IO_METHOD_READ:
			free(buffers[0].start);
			break;
		case IO_METHOD_MMAP:
			for (i = 0;i < n_buffers;++i)
				if (-1 == munmap(buffers[i].start, buffers[i].length))
					errno_exit("munmap");
			break;
		case IO_METHOD_USERPTR:
			for (i = 0;i < n_buffers;++i)
				free(buffers[i].start);
			break;
	}
}
static void init_frambuffer(const char *devfile)
{
	long int screensize = 0;
    int fbFd = 0;
	fbFd = open (devfile, O_RDWR);
    if (fbFd == -1)
    {
        perror ("Error: cannot open framebuffer device");
        exit (1);
    }

    if (ioctl (fbFd, FBIOGET_FSCREENINFO, &finfo) == -1)
    {
        perror ("Error reading fixed information");
        exit (2);
    }

	if (ioctl (fbFd, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        perror ("Error reading variable information");
        exit (3);
    }
    screensize = finfo.smem_len;
    /* Map the device to memory */
    frameBuffer =
        (unsigned short *) mmap (0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,fbFd, 0);
    if (frameBuffer == MAP_FAILED)
    {
        perror ("Error: Failed to map framebuffer device to memory");
        exit (4);
    }
    memset(frameBuffer,0,screensize);
}
/*./camera_test 0 0 320 240 320 240 0 \*/
int main(int argc,char **argv)
{
    const char *devfile = "/dev/fb0";
	cv_param video_param;
 
	if (argc <2){
		printf("usage: ./camera_test [buffer count]\n"
				"win_x     window x\n"
				"win_y     window y\n"
				"win_w     window width\n"
				"win_h     window height\n"
				"width    the width image\n"
				"height    the height image\n"
				"format    1 is to file 0 is to lcd\n"
				"device    /dev/videox\n"
				"-help     display this information\n");
        return 0;
	} 

	buffer_count = atoi(argv[1]);
	win_xx = atoi(argv[2]);
	win_yy = atoi(argv[3]);
	win_w = atoi(argv[4]);
	win_h = atoi(argv[5]);
	width = atoi(argv[6]);
	height = atoi(argv[7]);
	 
	scale = (width*height) / (win_w*win_h);
	printf("scale = %d\n",scale);
	if(scale <= 1)
		scale = 1;
	video_param.format = PF_YUV420;
	video_param.width = width;
	video_param.height = height;
	video_param.disp_top = 0;
	video_param.disp_left = 0;
	video_param.disp_width = SCREEN_WIDTH;
	video_param.disp_height = SCREEN_HEIGHT; 

	
	init_frambuffer(devfile);
	io = IO_METHOD_MMAP;
	open_device();
	init_device();
	start_capturing();
	mainloop();
	printf("111111111111\n");
	stop_capturing();
	printf("2222222222222\n");
	uninit_device();
	printf("333333333333\n");
	close_device();	
	printf("4444444444444\n");
	return 0;
}

