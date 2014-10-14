/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

#include "application.h"
#include "business_logic.h"

namespace vcamdb
{

/// ############################################################################
///			class business_logic
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
    /// ------------------------------------------------------------------------
    ///	free_memory( )
    /// ------------------------------------------------------------------------
    void business_logic::free_memory( )
    {
        /*
        if( this->_model_ad )
        {
            delete _model_ad;
        }
        if( this->_model_mr )
        {
            delete _model_mr;
        }
        if( this->_model_mediator )
        {
            delete _model_mediator;
        }
        if( this->_model_request )
        {
            delete _model_request;
        }
        if( this->_model_request_category )
        {
            delete _model_request_category;
        }
        if( this->_model_address )
        {
            delete _model_address;
        }
        if( this->_model_declarant_type )
        {
            delete _model_declarant_type;
        }
        */
    }

	/// ------------------------------------------------------------------------
	///	init( )
    /// ------------------------------------------------------------------------
	void business_logic::init( )
	{
		try
		{
            //this->init_db_path( );
            this->init_data_models( );
		}
		catch( std::exception &ex )
		{
			QString s_msg(
							"business_logic::init( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
			QString s_msg(
						"business_logic::init( )"
						":\n\t unknown error while initialize business logic"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
	}
	/// ------------------------------------------------------------------------
	///	exit( )
    /// ------------------------------------------------------------------------
	void business_logic::exit( )
	{
        this->free_memory( );

		qDebug( ) << "correctly exiting business logic";
	}

    /// ------------------------------------------------------------------------
    ///	init_data_models( )
    /// ------------------------------------------------------------------------
    void business_logic::init_data_models( )
    {
        /*
        this->init_model_ad( );

        this->init_model_mr( );

        this->init_model_mediator( );

        this->init_model_request( );

        this->init_model_request_category( );

        this->init_model_address( );

        this->init_model_declarant_type( );
        */
    }

/// ############################################################################

}//namespace vcamdb
