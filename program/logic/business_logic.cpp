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

#include "data_model_cam_selection.h"
#include "data_model_violation.h"
#include "data_model_camera.h"
#include "data_model_camera_object.h"

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
        if( this->_model_cam_selection )
        {
            delete _model_cam_selection;
        }
        if( this->_model_violation )
        {
            delete _model_violation;
        }
        if( this->_model_camera )
        {
            delete _model_camera;
        }
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
        this->init_model_cam_selection( );

        this->init_model_violation( );

        this->init_model_camera( );

        this->init_model_camera_object( );
    }

    /// ------------------------------------------------------------------------
    ///	init_model_cam_selection( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_cam_selection( )
    {
        this->_model_cam_selection = new data_model_cam_selection;
    }

    /// ------------------------------------------------------------------------
    ///	init_model_violation( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_violation( )
    {
        this->_model_violation = new data_model_violation;
    }

    /// ------------------------------------------------------------------------
    ///	init_model_camera( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_camera( )
    {
        this->_model_camera = new data_model_camera;
    }

    /// ------------------------------------------------------------------------
    ///	init_model_camera_object( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_camera_object( )
    {
        this->_model_camera_object = new data_model_camera_object;
    }

/// ############################################################################

}//namespace vcamdb
