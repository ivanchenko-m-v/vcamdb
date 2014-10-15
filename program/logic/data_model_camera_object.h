/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================

#ifndef __DATA_MODEL_CAMERA_OBJECT_H__
#define __DATA_MODEL_CAMERA_OBJECT_H__

#include <QAbstractTableModel>
#include <QList>
#include <QVector>

namespace vcamdb
{

    //class data_request;
    //class data_request_collection;
/// ############################################################################
///			class data_model_camera_object
/// ############################################################################
    class data_model_camera_object : public QAbstractTableModel
	{

	Q_OBJECT
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_model_camera_object( QObject* pobj = 0 );
	/// ------------------------------------------------------------------------
        virtual ~data_model_camera_object( );

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
        data_model_camera_object& operator=( const data_model_camera_object &rhs );

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
            this -> _header.append( QObject::tr( "OBJECT_TYPE" ) );
            this -> _header.append( QObject::tr( "OBJECT_ID" ) );
            this -> _header.append( QObject::tr( "OBJECT_NAME" ) );
            this -> _header.append( QObject::tr( "OBJECT_VIEW_GRADE" ) );
            this -> _header.append( QObject::tr( "DATE_OF_RECORD" ) );
            this -> _header.append( QObject::tr( "USER_CREATED" ) );
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

    };//class data_model_camera_object
/// ############################################################################

}//namespace vcamdb

#endif // __DATA_MODEL_CAMERA_OBJECT_H__
