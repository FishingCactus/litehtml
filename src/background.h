#pragma once
#include "types.h"
#include "attributes.h"
#include "css_length.h"
#include "css_position.h"
#include "web_color.h"
#include "borders.h"

namespace litehtml
{
	class background
	{
	public:
		tstring					m_image;
		tstring					m_baseurl;
		web_color				m_color;
        float                   m_opacity;
		background_attachment	m_attachment;
		css_position			m_position;
		background_repeat		m_repeat;
		background_box			m_clip;
		background_box			m_origin;
		css_border_radius		m_radius;

	public:
		background(void);
		background(const background& val);
		~background(void);

		background& operator=(const background& val);
	};

	class background_paint
	{
	public:
		tstring					image;
		tstring					baseurl;
		background_attachment	attachment;
		background_repeat		repeat;
		web_color				color;
		position				clip_box;
		position				origin_box;
		position				border_box;
		border_radiuses			border_radius;
		size					image_size;
        float                   opacity;
		int						position_x;
		int						position_y;
		bool					is_root;
	public:
		background_paint();
		background_paint(const background_paint& val);
		void operator=(const background& val);
	};

}