#include "../include/fdf.h"

void	pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->linel + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

static int set_i_d(int *d)
{
	if (*d < 0)
	{
		*d = -(*d);
		return (-1);
	}
	return (1);
}

void	line_low(t_fdf *fdf, t_pixel p1, t_pixel p2)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	yi = set_i_d(&dy);
	d = 2 * dy - dx;
	while (p1.x < p2.x)
	{
		pixel_put(&(fdf->mlx), p1.x, p1.y, p1.color);
		if (d > 0)
		{
			p1.y += yi;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		p1.x += 1;
	}
}

void	line_high(t_fdf *fdf, t_pixel p1, t_pixel p2)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	xi = set_i_d(&dx);
	d = 2 * dx - dy;
	while (p1.y < p2.y)
	{
		pixel_put(&(fdf->mlx), p1.x, p1.y, p1.color);
		if (d > 0)
		{
			p1.x += xi;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		p1.y += 1;
	}
}

/**
 * reminder: p1.x = x0, p1.y = y0, p2.x = x1, p2.y = y1**/
void draw_line(t_fdf *fdf, t_pixel p1, t_pixel p2)  
{
	if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
	{
		
		if (p1.x > p2.x)
			line_low(fdf, (t_pixel){p2.x, p2.y, p2.color}, (t_pixel){p1.x, p1.y, p1.color});
		else
			line_low(fdf, (t_pixel){p1.x, p1.y, p1.color}, (t_pixel){p2.x, p2.y, p2.color});
	}
	else
	{
		if (p1.y > p2.y)
			line_high(fdf, (t_pixel){p2.x, p2.y, p2.color}, (t_pixel){p1.x, p1.y, p1.color});
		else
			line_high(fdf, (t_pixel){p1.x, p1.y, p1.color}, (t_pixel){p2.x, p2.y, p2.color});
	}
}