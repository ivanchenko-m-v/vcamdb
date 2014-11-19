/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 19-11-2014
///		Comment		:
/// ============================================================================
#include <QDebug>

#include "data_model_violation.h"
#include "data_adapter_violation.h"

namespace vcamdb
{

/// ############################################################################
///			class data_model_violation
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
    ///	data_model_violation( )
	/// ------------------------------------------------------------------------
    data_model_violation::data_model_violation( QObject *pobj/* = 0*/ ) :
		QAbstractTableModel( pobj )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
    ///	~data_model_violation( )
	/// ------------------------------------------------------------------------
    data_model_violation::~data_model_violation( )
	{
		this->clear( );

        qDebug( ) << "data_model_violation cleared correctly";
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	violation( int i_row )
	/// ------------------------------------------------------------------------
    const data_violation* data_model_violation::violation( int i_row ) const
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
    void data_model_violation::clear( )
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
    void data_model_violation::initialize( )
	{
		this->init_columns_header( );
	}

	/// ------------------------------------------------------------------------
	///	refresh( const QVector<QVector<QVariant> > &data )
	/// ------------------------------------------------------------------------
    void data_model_violation::refresh(const QVector<QVector<QVariant> > &data)
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
            data_violation *violation = new data_violation( *iter );
			this->_list.append( violation );
		}
		this->endInsertRows( );
	}

	/// ------------------------------------------------------------------------
    ///	refresh( data_violation_collection *data )
	/// ------------------------------------------------------------------------
    void data_model_violation::refresh( data_violation_collection *data )
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
    ///	append(const data_violation &violation)
	/// ------------------------------------------------------------------------
    void data_model_violation::append( const data_violation &violation )
    {
        //вставка в конец списка
		this->beginInsertRows( QModelIndex( ), this->_list.size( ), this->_list.size( ) );

        data_violation *pr = new data_violation( violation );
        //вставка в конец списка
		this->_list.append( pr );

        this->endInsertRows( );
    }

	/// ------------------------------------------------------------------------
    ///	prepend(const data_violation &violation)
	/// ------------------------------------------------------------------------
    void data_model_violation::prepend( const data_violation &violation )
    {
        //вставка в начало списка
		this->beginInsertRows( QModelIndex( ), 0, 0 );

        data_violation *pr = new data_violation( violation );
        //вставка в начало списка
		this->_list.prepend( pr );

        this->endInsertRows( );
    }

	/// ------------------------------------------------------------------------
    ///	update(const data_violation &violation)
	/// ------------------------------------------------------------------------
    void data_model_violation::update( const data_violation &violation )
    {
        if( violation.id_violation() == 0 )
        {
            return;
        }
        data_violation *pv = this->find( violation.id_violation( ) );
        if( pv )
        {
            *pv = violation;
        }
    }

	/// ------------------------------------------------------------------------
    ///	find( int id_violation )
	/// ------------------------------------------------------------------------
    data_violation* data_model_violation::find( int id_violation )
    {
        data_violation *result = 0;

        data_violation_list::iterator it = this->_list.begin( );
        for( ;it < this->_list.end( ); ++it )
        {
            data_violation *v = *it;
            if( v && v->id_violation( ) == id_violation )
            {
                result = v;
                break;
            }
        }
        return result;
    }

	/// ------------------------------------------------------------------------
    ///	row_index( int id_violation )
	/// ------------------------------------------------------------------------
    int data_model_violation::row_index( int id_violation )
    {
        int n_row = -1;//out of list

        data_violation_list::iterator it = this->_list.begin( );
        for( ;it < this->_list.end( ); ++it )
        {
            ++n_row;

            data_violation *v = *it;
            if( v && v->id_violation( ) == id_violation )
            {
                break;
            }
        }
        return n_row;
    }

	/// ------------------------------------------------------------------------
	/// virtual
	///	data( )
	/// ------------------------------------------------------------------------
    QVariant data_model_violation::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
		if( !index.isValid( ) )
		{
			return QVariant( );
		}
        data_violation* pv = this->_list.at( index.row( ) );
        if( !pv )
        {
            return QVariant( );
        }
		switch( index.column( ) )
		{
            case 0:
                return pv->date_record( );
            case 1:
                return pv->date_violation( );
			case 2:
                return pv->violation_type( );
            case 3:
                return pv->okrug( );
            case 4:
                return pv->district( );
            case 5:
                return pv->cam_name( );
            case 6:
                return pv->object_type( );
            case 7:
                return pv->object_id( );
            case 8:
                return pv->object_name( );
            case 9:
                return pv->URL( );
            case 10:
                return pv->user( );
            default:
				return QVariant( );
		}
		return QVariant( );
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	setData( )
	/// ------------------------------------------------------------------------
    bool data_model_violation::setData(
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
    Qt::ItemFlags data_model_violation::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	/// ------------------------------------------------------------------------
    bool data_model_violation::insertRows(
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
            data_violation* violation = new data_violation;
			this->_list.insert( row + i, violation );
		}

		this->endInsertRows( );

		return true;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	/// ------------------------------------------------------------------------
    bool data_model_violation::removeRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		this->beginRemoveRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; ++i )
		{
            data_violation *item = this->_list.takeAt( row );
			delete item;
		}

		this->endRemoveRows( );

		return true;
	}

}//namespace vcamdb
