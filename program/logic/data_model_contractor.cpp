/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-02-2015
///		Date update	: 18-02-2015
///		Comment		:
/// ============================================================================
#include <QDebug>

#include "data_model_contractor.h"
#include "data_adapter_contractor.h"

namespace vcamdb
{

/// ############################################################################
///			class data_model_contractor
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
    ///	data_model_contractor( )
	/// ------------------------------------------------------------------------
    data_model_contractor::data_model_contractor( QObject *pobj/* = 0*/ ) :
		QAbstractTableModel( pobj )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
    ///	~data_model_contractor( )
	/// ------------------------------------------------------------------------
    data_model_contractor::~data_model_contractor( )
	{
		this->clear( );

        qDebug( ) << "data_model_contractor cleared correctly";
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// ------------------------------------------------------------------------
    ///	violation_type( int i_row )
	/// ------------------------------------------------------------------------
    const data_contractor* data_model_contractor::violation_type( int i_row ) const
	{
		if( i_row < 0 || i_row >= this->_list.size( ) )
		{
			return 0;
		}
		return this->_list.at( i_row );
	}

    /// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	clear( )
	/// ------------------------------------------------------------------------
    void data_model_contractor::clear( )
	{
        if( !this->_list.size( ) )
        {
            return;
        }
		this->removeRows( 0, this->_list.size( ) );
		this->_list.clear( );
	}

	/// ------------------------------------------------------------------------
	///	initialize( )
	/// ------------------------------------------------------------------------
    void data_model_contractor::initialize( )
	{
		this->init_columns_header( );
	}

	/// ------------------------------------------------------------------------
	///	refresh( const QVector<QVector<QVariant> > &data )
	/// ------------------------------------------------------------------------
    void data_model_contractor::refresh(const QVector<QVector<QVariant> > &data)
	{
		this->clear( );

		if( !data.count( ) )
		{
			//if no data
			return;
		}
		this->beginInsertRows( QModelIndex( ), 0, data.count( ) - 1 );

		QVector<QVector<QVariant> >::const_iterator iter;
		for( iter = data.constBegin( ); iter != data.end( ); ++iter )
		{
            data_contractor *request = new data_contractor( *iter );
			this->_list.append( request );
		}
		this->endInsertRows( );
	}

	/// ------------------------------------------------------------------------
    ///	refresh( data_contractor_collection *data )
	/// ------------------------------------------------------------------------
    void data_model_contractor::refresh( data_contractor_collection *data )
	{
		this->clear( );

		if( !data || !data->size( ) )
		{
			//if no data
			return;
		}
		this->beginInsertRows( QModelIndex( ), 0, data->size( ) - 1 );

		this->_list.append( *( data->list( ) ) );
		data->free_data_pointer( );

        this->endInsertRows( );
    }

	/// ------------------------------------------------------------------------
    ///	insert(const data_contractor &request)
	/// ------------------------------------------------------------------------
    void data_model_contractor::insert( const data_contractor &record )
    {
		this->beginInsertRows( QModelIndex( ), this->_list.size( ), this->_list.size( ) );

        data_contractor *pr = new data_contractor( record );
		this->_list.append( pr );

        this->endInsertRows( );
    }

	/// ------------------------------------------------------------------------
	/// virtual
	///	data( )
	/// ------------------------------------------------------------------------
    QVariant data_model_contractor::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
		if( !index.isValid( ) )
		{
			return QVariant( );
		}
        data_contractor *record = this->_list.at( index.row( ) );
        if( !record )
        {
            return QVariant( );
        }

		switch( index.column( ) )
		{
            case data_contractor::num_field_object_type:
                return record->object_type( );
            case data_contractor::num_field_contractor:
                return record->contractor( );
			default:
				return QVariant( );
		}
		return QVariant( );
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	setData( )
	/// ------------------------------------------------------------------------
    bool data_model_contractor::setData(
										const QModelIndex &/*index*/,
										const QVariant &/*value*/,
										int /*role //= Qt::EditRole*/
									  )
	{
		return false;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	flags( )
	/// ------------------------------------------------------------------------
    Qt::ItemFlags data_model_contractor::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	/// ------------------------------------------------------------------------
    bool data_model_contractor::insertRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
        if( ( row < 0 ) || ( row > this->_list.size( ) ) )
		{
			return false;
		}
		this->beginInsertRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; i++ )
		{
            data_contractor* request = new data_contractor;
			this->_list.insert( row + i, request );
		}

		this->endInsertRows( );

		return true;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	/// ------------------------------------------------------------------------
    bool data_model_contractor::removeRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
        this->beginRemoveRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; ++i )
		{
            data_contractor *item = this->_list.takeAt( row );
			delete item;
		}

		this->endRemoveRows( );

		return true;
	}

}//namespace vcamdb
