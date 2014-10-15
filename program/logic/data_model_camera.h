/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================

#ifndef __DATA_MODEL_CAMERA_H__
#define __DATA_MODEL_CAMERA_H__

#include <QAbstractTableModel>
#include <QList>
#include <QVector>

namespace vcamdb
{

    //class data_request;
    //class data_request_collection;
/// ############################################################################
///			class data_model_camera
/// ############################################################################
    class data_model_camera : public QAbstractTableModel
	{

	Q_OBJECT
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_model_camera( QObject* pobj = 0 );
	/// ------------------------------------------------------------------------
        virtual ~data_model_camera( );

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
        data_model_camera& operator=( const data_model_camera &rhs );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		virtual void initialize( void );
	/// ------------------------------------------------------------------------
		virtual void init_columns_header( void )
		{
            this -> _header.append( QObject::tr( "CAM_ID" ) );
            this -> _header.append( QObject::tr( "CAM_NAME" ) );
            this -> _header.append( QObject::tr( "CAM_ADDRESS" ) );
            this -> _header.append( QObject::tr( "CAM_TYPE" ) );
            this -> _header.append( QObject::tr( "INSPECTION_FLAG" ) );
            this -> _header.append( QObject::tr( "OVERVIEW_TYPE" ) );
            this -> _header.append( QObject::tr( "SELECTION" ) );
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

    };//class data_model_camera
/// ############################################################################

}//namespace vcamdb

#endif // __DATA_MODEL_CAMERA_H__
