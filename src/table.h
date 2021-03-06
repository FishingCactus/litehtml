#pragma once

namespace litehtml
{
	struct table_row
	{
		typedef std::vector<table_row>	vector;

		int				height;
		int				border_top;
		int				border_bottom;
		element*		el_row;
		int				top;
		int				bottom;
		css_length		css_height;
		int				min_height;

		table_row()
		{
			min_height		= 0;
			top				= 0;
			bottom			= 0;
			border_bottom	= 0;
			border_top		= 0;
			height			= 0;
			el_row			= nullptr;
			css_height.predef(0);
		}

		table_row(int h, element* row)
		{
			min_height		= 0;
			height			= h;
			el_row			= row;
			border_bottom	= 0;
			border_top		= 0;
			top				= 0;
			bottom			= 0;
			if (row)
			{
				css_height = row->get_css_height();
			}
		}
	};

	struct table_column
	{
		typedef std::vector<table_column>	vector;

		int			min_width;
		int			max_width;
		int			width;
		css_length	css_width;
		int			border_left;
		int			border_right;
		int			left;
		int			right;

		table_column()
		{
			left			= 0;
			right			= 0;
			border_left		= 0;
			border_right	= 0;
			min_width		= 0;
			max_width		= 0;
			width			= 0;
			css_width.predef(0);
		}

		table_column(int min_w, int max_w)
		{
			left			= 0;
			right			= 0;
			border_left		= 0;
			border_right	= 0;
			max_width		= max_w;
			min_width		= min_w;
			width			= 0;
			css_width.predef(0);
		}
	};

	class table_column_accessor
	{
	public:
		virtual int& get(table_column& col) = 0;
	};

	class table_column_accessor_max_width : public table_column_accessor
	{
	public:
		virtual int& get(table_column& col);
	};

	class table_column_accessor_min_width : public table_column_accessor
	{
	public:
		virtual int& get(table_column& col);
	};

	class table_column_accessor_width : public table_column_accessor
	{
	public:
		virtual int& get(table_column& col);
	};

	struct table_cell
	{
		element*		el;
		int				colspan;
		int				rowspan;
		int				min_width;
		int				min_height;
		int				max_width;
		int				max_height;
		int				width;
		int				height;
		margins			borders;

		table_cell()
		{
			min_width		= 0;
			min_height		= 0;
			max_width		= 0;
			max_height		= 0;
			width			= 0;
			height			= 0;
			colspan			= 1;
			rowspan			= 1;
			el				= 0;
		}

	};

	class table_grid
	{
	public:
		typedef std::vector< std::vector<table_cell> >	rows;
	private:
		int						m_rows_count;
		int						m_cols_count;
		rows					m_cells;
		table_column::vector	m_columns;
		table_row::vector		m_rows;
	public:

		table_grid()
		{
			m_rows_count	= 0;
			m_cols_count	= 0;
		}

		void			clear();
		void			begin_row(element* row);
		void			add_cell(element* el);
		bool			is_rowspanned(int r, int c);
		void			finish();
		table_cell*		cell(int t_col, int t_row);
		table_column&	column(int c)	{ return m_columns[c];	}
		table_row&		row(int r)		{ return m_rows[r];		}

		int				rows_count()	{ return m_rows_count;	}
		int				cols_count()	{ return m_cols_count;	}

		void			distribute_max_width(int width, int start, int end);
		void			distribute_min_width(int width, int start, int end);
		void			distribute_width(int width, int start, int end);
		void			distribute_width(int width, int start, int end, table_column_accessor* acc);
		int				calc_table_width(int block_width, bool is_auto, int& min_table_width, int& max_table_width);
		void			calc_horizontal_positions(margins& table_borders, border_collapse bc, int bdr_space_x);
		void			calc_vertical_positions(margins& table_borders, border_collapse bc, int bdr_space_y);
		void			calc_rows_height(int blockHeight, int borderSpacingY);
	};
}
