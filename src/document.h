#pragma once
#include "object.h"
#include "style.h"
#include "types.h"
#include "context.h"
#include "event_handler.h"
#include "gumbo/gumbo.h"

namespace litehtml
{
	struct css_text
	{
		typedef std::vector<css_text>	vector;

		tstring	text;
		tstring	baseurl;
		tstring	media;

		css_text()
		{
		}

		css_text(const tchar_t* txt, const tchar_t* url, const tchar_t* media_str)
		{
			text	= txt ? txt : _t("");
			baseurl	= url ? url : _t("");
			media	= media_str ? media_str : _t("");
		}

		css_text(const css_text& val)
		{
			text	= val.text;
			baseurl	= val.baseurl;
			media	= val.media;
		}
	};

	struct stop_tags_t
	{
		const litehtml::tchar_t*	tags;
		const litehtml::tchar_t*	stop_parent;
	};

	struct ommited_end_tags_t
	{
		const litehtml::tchar_t*	tag;
		const litehtml::tchar_t*	followed_tags;
	};

	class html_tag;

	class document : public object
	{
	public:
		typedef object_ptr<document>	ptr;
	private:
		element::ptr						m_root;
		document_container*					m_container;
		event_handler::ptr					m_event_handler;
		fonts_map							m_fonts;
		css_text::vector					m_css;
		litehtml::css						m_styles;
		litehtml::web_color					m_def_color;
		litehtml::context*					m_context;
		litehtml::size						m_size;
		position::vector					m_fixed_boxes;
		media_query_list::vector			m_media_lists;
		element::ptr						m_over_element;
		element::ptr						m_active_element;
		elements_vector						m_tabular_elements;
		media_features						m_media;
		tstring							 m_lang;
		tstring							 m_culture;
	public:
		document(litehtml::document_container* objContainer, litehtml::context* ctx);
		virtual ~document();

		litehtml::document_container*	container()	{ return m_container; }
		const litehtml::document_container*	container() const	{ return m_container; }
		const litehtml::css&			styles() { return m_styles; }
		uint_ptr						get_font(const tchar_t* name, int size, const tchar_t* weight, const tchar_t* style, const tchar_t* decoration, font_metrics* fm);
		int								render(int max_width, render_type rt = render_all);
		void							draw(uint_ptr hdc, int x, int y, const position* clip);
		web_color						get_def_color()	{ return m_def_color; }
		int								cvt_units(const tchar_t* str, int fontSize, bool* is_percent = 0) const;
		int								cvt_units(css_length& val, int fontSize, int size = 0) const;
		int								width() const;
		int								height() const;
		void							add_stylesheet(const tchar_t* str, const tchar_t* baseurl, const tchar_t* media);
		bool							on_mouse_move(int x, int y, int client_x, int client_y);
		bool							on_lbutton_down();
		bool							on_lbutton_up();
		litehtml::element::ptr			create_element(const tchar_t* tag_name, const string_map& attributes);
		element::ptr					root();
		const element::ptr				root() const;
		element::ptr					active_element();
		const element::ptr				active_element() const;
		void							get_fixed_boxes(position::vector& fixed_boxes);
		void							add_fixed_box(const position& pos);
		void							add_media_list(media_query_list::ptr list);
		bool							media_changed();
		bool							lang_changed();
		bool							match_lang(const tstring & lang);
		void							add_tabular(element::ptr el);
		void							set_event_handler(event_handler::ptr eh);
		event_handler *					get_event_handler();
		void							finalize();

		static litehtml::document::ptr createEmptyDocument(litehtml::document_container* objPainter, litehtml::context* ctx);
		static litehtml::document::ptr createFromString(const tchar_t* str, litehtml::document_container* objPainter, litehtml::context* ctx, litehtml::css* user_styles = 0, litehtml::document::ptr doc = nullptr);
		static litehtml::document::ptr createFromUTF8(const char* str, litehtml::document_container* objPainter, litehtml::context* ctx, litehtml::css* user_styles = 0, litehtml::document::ptr doc = nullptr);
		static bool createElements(elements_vector & elements, litehtml::document * document, const char* text, litehtml::element * parent_element = nullptr, litehtml::css* user_styles = nullptr);

	private:
		document();
		litehtml::uint_ptr	add_font(const tchar_t* name, int size, const tchar_t* weight, const tchar_t* style, const tchar_t* decoration, font_metrics* fm);

		void create_node(GumboNode* node, elements_vector& elements);
		bool update_media_lists(const media_features& features);
		void fix_tables_layout();
		void fix_table_children(element::ptr el_ptr, style_display disp, const tchar_t* disp_str);
		void fix_table_parent(element::ptr el_ptr, style_display disp, const tchar_t* disp_str);
	};

	inline element::ptr document::root()
	{
		return m_root;
	}
	inline const element::ptr document::root() const
	{
		return m_root;
	}
	inline element::ptr document::active_element()
	{
		return m_active_element;
	}
	inline const element::ptr document::active_element() const
	{
		return m_active_element;
	}
	inline void document::add_tabular(element::ptr el)
	{
		m_tabular_elements.push_back(el);
	}
	inline void document::set_event_handler(event_handler::ptr eh)
	{
		m_event_handler = eh;
	}
	inline event_handler * document::get_event_handler()
	{
		return m_event_handler;
	}
	inline bool document::match_lang(const tstring & lang)
	{
		return lang == m_lang || lang == m_culture;
	}
}
