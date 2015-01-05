/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-11-2014
///		Date update	: 06-01-2015
///		Comment		:
/// ============================================================================

#ifndef __DATA_MODEL_VIOLATION_TYPE_H__
#define __DATA_MODEL_VIOLATION_TYPE_H__

#include <QAbstractTableModel>
#include <QList>
#include <QVector>

namespace vcamdb
{

    class data_violation_type;
    class data_violation_type_collection;

    typedef QList<data_violation_type*> data_violation_type_list;
/// ############################################################################
///			class data_model_violation_type
/// ############################################################################
    class data_model_violation_type : public QAbstractTableModel
	{

	Q_OBJECT
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_model_violation_type( QObject* pobj = 0 );
	/// ------------------------------------------------------------------------
        virtual ~data_model_violation_type( );

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        const data_violation_type* violation_type( int i_row ) const;
    ///-------------------------------------------------------------------------
        const data_violation_type_list& list( ) const
        { return this->_list; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        data_model_violation_type& operator=( const data_model_violation_type &rhs );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		virtual void initialize( void );
	/// ------------------------------------------------------------------------
		virtual void init_columns_header( void )
		{
            this -> _header.append( QObject::tr( "violation_type" ) );
            this -> _header.append( QObject::tr( "violation_type_description" ) );
        }

	public:
	/// ------------------------------------------------------------------------
		void clear( );
	/// ------------------------------------------------------------------------
		void refresh( const QVector<QVector<QVariant> > &data );
	/// ------------------------------------------------------------------------
        void refresh( data_violation_type_collection *data );
	/// ------------------------------------------------------------------------
        void insert( const data_violation_type &record );
	/// ------------------------------------------------------------------------
	/// override
		virtual int rowCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							) const
		{
            return this -> _list.size( );
        }
	/// ------------------------------------------------------------------------
	/// override
		virtual int columnCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							   ) const
		{
			return this -> _header.size( );
		}
	/// ------------------------------------------------------------------------
	/// override
		virtual QVariant headerData(
									int section,
									Qt::Orientation orientation,
									int role/* = Qt::DisplayRole*/
								   ) const
		{
			if( role != Qt::DisplayRole )
			{
				return QVariant( );
			}
			if(
				( section > this -> _header.size( ) ) ||
				( section < 0 )
			  )
			{
				return QVariant( );
			}

			return ( orientation == Qt::Horizontal )
					? ( this -> _header )[section]
					: " ";
		}
	/// ------------------------------------------------------------------------
	/// override
		virtual Qt::ItemFlags flags( const QModelIndex &index ) const;
	/// ------------------------------------------------------------------------
	/// override
		virtual QVariant data(
								const QModelIndex & index,
								int role = Qt::DisplayRole
							 ) const;
	/// ------------------------------------------------------------------------
	/// override
		virtual bool setData(
								const QModelIndex & index,
								const QVariant & value,
								int role = Qt::EditRole
							 );
	/// ------------------------------------------------------------------------
	/// override
		virtual bool insertRows(
								int row, int count,
								const QModelIndex &parent = QModelIndex( )
							   );
	/// ------------------------------------------------------------------------
	/// override
		virtual bool removeRows(
								int row, int count,
								const QModelIndex &parent = QModelIndex( )
							   );

	/// ========================================================================
	///		SLOTS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        data_violation_type_list	_list;
        QVector<QString>    	_header;

    };//class data_model_violation_type
/// ############################################################################

}//namespace vcamdb

#endif // __DATA_MODEL_VIOLATION_TYPE_H__
