/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================

#ifndef __DATA_MODEL_CAM_SELECTION_H__
#define __DATA_MODEL_CAM_SELECTION_H__

#include <QAbstractTableModel>
#include <QList>
#include <QVector>

namespace vcamdb
{

    //class data_request;
    //class data_request_collection;
/// ############################################################################
///			class data_model_cam_selection
/// ############################################################################
    class data_model_cam_selection : public QAbstractTableModel
	{

	Q_OBJECT
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_model_cam_selection( QObject* pobj = 0 );
	/// ------------------------------------------------------------------------
        virtual ~data_model_cam_selection( );

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        //const data_request* request( int i_row ) const;

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        data_model_cam_selection& operator=( const data_model_cam_selection &rhs );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		virtual void initialize( void );
	/// ------------------------------------------------------------------------
		virtual void init_columns_header( void )
		{
            this -> _header.append( QObject::tr( "cam_name" ) );
            this -> _header.append( QObject::tr( "address" ) );
		}

	public:
	/// ------------------------------------------------------------------------
		void clear( );
	/// ------------------------------------------------------------------------
		void refresh( const QVector<QVector<QVariant> > &data );
	/// ------------------------------------------------------------------------
        //void refresh( data_request_collection *data );
	/// ------------------------------------------------------------------------
        //void insert( const data_request &request );
	/// ------------------------------------------------------------------------
	/// override
		virtual int rowCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							) const
		{
//			return this -> _list.size( );
            return 10;
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
        //QList<data_request*>	_list;
		QVector<QString>		_header;

    };//class data_model_cam_selection
/// ############################################################################

}//namespace vcamdb

#endif // __DATA_MODEL_CAM_SELECTION_H__
