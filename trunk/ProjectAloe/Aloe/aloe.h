#ifndef ALOE_INCLUDED_ALOE_H
#define ALOE_INCLUDED_ALOE_H

#pragma warning(disable:4250)

#include "Aloe/aloePropertyMap.h"
#include "Aloe/aloeFormat.h"

#define aloe__method( I, N, Ret, Args ) \
    typedef aloe__##Ret  N##__resultType; \
    typedef aloe__##Args N##__argsType; \
    virtual N##__resultType N ( const N##__argsType & ) = 0;

#define aloe__indexer_none( I, N, IndexType, ValueType, Getter, Setter, AR, AA, RR, RA, Appender, Remover, ResultType, ArgsType, Caller ) \
    typedef aloe__##ValueType N##__valueType;\
    typedef aloe__##AR    N##__appendResultType;\
    typedef aloe__##AA    N##__appendArgType;\
    typedef aloe__##RR    N##__removeResultType;\
    typedef aloe__##RA    N##__removeArgType;\
    typedef aloe__##ResultType N##__resultType;\
    typedef aloe__##ArgsType   N##__argsType;\
    aloe__property__( I, N, N##__valueType, \
            N##__appendResultType, N##__appendArgType, N##__removeResultType, N##__removeArgType, \
            N##__resultType, N##__argsType, Getter, Setter, Appender, Remover, Caller )

#define aloe__indexer_____ aloe__indexer_none
#define aloe__indexer_ aloe__indexer_none

#define aloe__indexer_map( I, N, IndexType, ValueType, Getter, Setter, AR, AA, RR, RA, Appender, Remover, ResultType, ArgsType, Caller ) \
    typedef aloe__##IndexType N##__indexType;\
    typedef aloe__##ValueType N##__valueType;\
    typedef aloe__##AR    N##__appendResultType;\
    typedef aloe__##AA    N##__appendArgType;\
    typedef aloe__##RR    N##__removeResultType;\
    typedef aloe__##RA    N##__removeArgType;\
    typedef aloe__##ResultType N##__resultType;\
    typedef aloe__##ArgsType   N##__argsType;\
    aloe__prop_map__( I, N, N##__valueType, \
            N##__appendResultType, N##__appendArgType, N##__removeResultType, N##__removeArgType, \
            N##__resultType, N##__argsType, N##__indexType, Getter, Setter, Appender, Remover, Caller )
    
#define aloe__prop( I, N, Indexer, IndexType, Getter, Setter, ValueType, Appender, AR, AA, Remover, RR, RA, Caller, ResultType, ArgsType ) \
    aloe__indexer_##Indexer( I, N, IndexType, ValueType, Getter, Setter, AR, AA, RR, RA, Appender, Remover, ResultType, ArgsType, Caller )
    
#define aloe__Query_impl_interfaces_0()
    
#define aloe__Query_impl_interfaces_1( I1 ) \
    if ( iid == aloe__iid_of( I1 )) \
    { \
        reinterpret_cast< I1 *& >( argPtr ) = this; \
        argCount = Aloe::Detail::add_ref( this ); \
        return true; \
    }

#define aloe__Query_impl_interfaces_2( I1, I2 ) \
    aloe__Query_impl_interfaces_1( I1 ) \
    else aloe__Query_impl_interfaces_1( I2 )

#define aloe__Query_impl_interfaces_3( I1, I2, I3 ) \
    aloe__Query_impl_interfaces_2( I1, I2 ) \
    else aloe__Query_impl_interfaces_1( I3 )

#define aloe__Query_impl_interfaces_4( I1, I2, I3, I4 ) \
    aloe__Query_impl_interfaces_3( I1, I2, I3 ) \
    else aloe__Query_impl_interfaces_1( I4 )

#define aloe__Query_impl_interfaces_5( I1, I2, I3, I4, I5 ) \
    aloe__Query_impl_interfaces_4( I1, I2, I3, I4 ) \
    else aloe__Query_impl_interfaces_1( I5 )

#define aloe__Query_impl_interfaces_6( I1, I2, I3, I4, I5, I6 ) \
    aloe__Query_impl_interfaces_5( I1, I2, I3, I4, I5 ) \
    else aloe__Query_impl_interfaces_1( I6 )

#define aloe__Query_impl_interfaces_7( I1, I2, I3, I4, I5, I6, I7 ) \
    aloe__Query_impl_interfaces_6( I1, I2, I3, I4, I5, I6 ) \
    else aloe__Query_impl_interfaces_1( I7 )

#define aloe__Query_impl_interfaces_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    aloe__Query_impl_interfaces_8( I1, I2, I3, I4, I5, I6, I7 ) \
    else aloe__Query_impl_interfaces_1( I8 )

#define aloe__Query_impl_interfaces_9( I1, I2, I3, I4, I5, I6, I7, I8, I9 ) \
    aloe__Query_impl_interfaces_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    else aloe__Query_impl_interfaces_1( I9 )

#define aloe__Query_impl_bases_0() \
    aloe__Query_impl_interfaces_1( Aloe::IProvider )

#define aloe__Query_impl_bases_1( B1 ) \
    if ( B1::Query( iid, argPtr, argCount )) { return true; }

#define aloe__Query_impl_bases_2( I1, I2 ) \
    aloe__Query_impl_bases_1( I1 ) \
    else aloe__Query_impl_bases_1( I2 )

#define aloe__Query_impl_bases_3( I1, I2, I3 ) \
    aloe__Query_impl_bases_2( I1, I2 ) \
    else aloe__Query_impl_bases_1( I3 )

#define aloe__Query_impl_bases_4( I1, I2, I3, I4 ) \
    aloe__Query_impl_bases_3( I1, I2, I3 ) \
    else aloe__Query_impl_bases_1( I4 )

#define aloe__Query_impl_bases_5( I1, I2, I3, I4, I5 ) \
    aloe__Query_impl_bases_4( I1, I2, I3, I4 ) \
    else aloe__Query_impl_bases_1( I5 )

#define aloe__Query_impl_bases_6( I1, I2, I3, I4, I5, I6 ) \
    aloe__Query_impl_bases_5( I1, I2, I3, I4, I5 ) \
    else aloe__Query_impl_bases_1( I6 )

#define aloe__Query_impl_bases_7( I1, I2, I3, I4, I5, I6, I7 ) \
    aloe__Query_impl_bases_6( I1, I2, I3, I4, I5, I6 ) \
    else aloe__Query_impl_bases_1( I7 )

#define aloe__Query_impl_bases_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    aloe__Query_impl_bases_8( I1, I2, I3, I4, I5, I6, I7 ) \
    else aloe__Query_impl_bases_1( I8 )

#define aloe__Query_impl_bases_9( I1, I2, I3, I4, I5, I6, I7, I8, I9 ) \
    aloe__Query_impl_bases_8( I1, I2, I3, I4, I5, I6, I7, I8 ) \
    else aloe__Query_impl_bases_1( I9 )


#define aloe__Query_impl( ICount, INames, BCount, BNames ) \
    Aloe::Types::Bool QueryCounterAddRef( Aloe::IRefCount * &pCount ) \
    { \
        pCount = Aloe::Detail::add_ref( this ); \
        return (0 != pCount);\
    } \
    Aloe::Types::Bool Query( const Aloe::Types::Identifier &iid, Aloe::Types::RawPointer &argPtr, Aloe::IRefCount * &argCount ) \
    { \
        aloe__Query_impl_interfaces_##ICount INames; \
        aloe__Query_impl_bases_##BCount BNames; \
        return false; \
    }
    
#define aloe__interface_common( I ) \
    static Aloe::Utils::SmartPtr< I > This( const Aloe::Utils::SmartPtr< I > &ptr ) \
    { \
        return ptr; \
    } \

#define aloe__interface( I ) struct I : virtual Aloe::IProvider

#define aloe__iid( I ) \
    static const Aloe::Types::Identifier & IId () \
    { \
        static Aloe::Types::Identifier s_IId = Aloe::GetIdOfName( aloe__string( #I )); \
        return s_IId; \
    } \
    aloe__interface_common( I )

#define aloe__iid__const( I, iid ) \
    enum { aloe_IID = iid }; \
    static const Aloe::Types::Identifier & IId () \
    { \
        static Aloe::Types::Identifier s_iid( Aloe::Types::LongPointer( iid )); \
        return s_iid; \
    } \
    aloe__interface_common( I )

#define aloe__method_imp( I, N, n ) aloe__resultRet( I, N ) N ( aloe__argsArg( I, N, n ) )

#define aloe__property_imp_get( I, N ) aloe__valueRet( I, N ) I::get_##N()
#define aloe__property_imp_put( I, N, n ) void I::put_##N( aloe__valueArg( I, N, n ))
#define aloe__property_imp_append( I, N, n ) aloe__appendRet( I, N ) I::append_##N( aloe__appendArg( I, N, n ))
#define aloe__property_imp_remove( I, N, n ) aloe__removeRet( I, N ) I::remove_##N( aloe__removeArg( I, N, n ))
#define aloe__property_imp_call( I, N, n ) aloe__resultRet( I, N ) I::call_##N( aloe__argsArg( I, N, n ))

#define aloe__prop_map_imp_get( I, N, i ) aloe__valueRet( I, N ) I::get_##N( aloe__indexArg( I, N, i ))
#define aloe__prop_map_imp_put( I, N, i, n ) void I::put_##N( aloe__indexArg( I, N, i ), aloe__valueArg( I, N, n ))
#define aloe__prop_map_imp_append( I, N, i, n ) aloe__appendRet( I, N ) I::append_##N( aloe__indexArg( I, N, i ), aloe__appendArg( I, N, n ))
#define aloe__prop_map_imp_remove( I, N, i, n ) aloe__removeRet( I, N ) I::remove_##N( aloe__indexArg( I, N, i ), aloe__removeArg( I, N, n ))
#define aloe__prop_map_imp_call( I, N, i, n ) aloe__resultRet( I, N ) I::call_##N( aloe__indexArg( I, N, i ), aloe__argsArg( I, N, n ))

#define aloe__runtime_method( I, N )
#define aloe__runtime_prop( I, N )
#define aloe__runtime_map( I, N )

#define aloe__iid_of( I ) I::IId()
#define aloe__iid_const_of( I ) I::aloe_IID

#define aloe__report( S ) { \
    char buffer[1024] = {0,}; \
    _snprintf( buffer, 1024, "%s(%i): %s\n", __FILE__, __LINE__, S ); \
    ::OutputDebugStringA( buffer ); }

#define aloe__try \
{ bool aloe__bTrialFailed = false; using namespace Aloe; \
    try {

#define aloe__retry \
    } catch( Errors::Error_InterfaceNotFound & ) { aloe__bTrialFailed = true; \
        aloe__report("interface not found - retrying"); \
    } if ( aloe__bTrialFailed ) try { aloe__bTrialFailed = false; \
        
#define aloe__finish \
    } catch( Errors::Error_InterfaceNotFound & ) { aloe__bTrialFailed = true; \
        aloe__report("interface not found - no trials left"); \
    } }



namespace Aloe {
    namespace Detail {

        inline IRefCount * add_ref( IRefCount *pCount )
        {
            pCount->AddRef();
            return pCount;
        }
        
        template< class Interface >
            IRefCount * add_ref( const Utils::SmartPtr< Interface > &ptr )
            {
                YOU_CANNOT_ADD_REF_OBJECT_KEPT_VIA_SMART_POINTER;
            }

        inline IRefCount * add_ref( ... )
        {
            return NULL;
        }

        
        template< class Interface, class R, class Meth >
            struct MethodCaller : Aloe::Utils::SmartPtr< Interface > 
            {
                Meth meth;

                MethodCaller( Meth m, const Aloe::Utils::SmartPtr< Interface > &p )
                    : meth( m )
                    , Aloe::Utils::SmartPtr< Interface >( p )
                {
                }

                R operator () ()
                {
                    return ((*(get())).*meth)();
                }
                
#define ALOE_PP_MethodCaller__Generic( N ) \
                template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) > \
                    R operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, )) \
                    {\
                        return ((*(get())).*meth)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) ); \
                    }
                
                ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, MethodCaller__Generic );
            };
        
        template< class Interface, class R ALOE_PP_TEMPLATE_MAX( COMMA, COMMA, class, B,, ) >
            struct MethodCaller< Interface, R
            , R (Interface::*) ( const Aloe::Types::Tuple< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, getClass, B,, ) > & ) >
            : Aloe::Utils::SmartPtr< Interface > 
            {
                typedef R (Interface::*Meth) ( const Aloe::Types::Tuple< ALOE_PP_TEMPLATE_MAX( NONE, COMMA, getClass, B,, ) > & );
                Meth meth;

                MethodCaller( Meth m, const Aloe::Utils::SmartPtr< Interface > &p )
                    : meth( m )
                    , Aloe::Utils::SmartPtr< Interface >( p )
                {
                }
                
                R operator () ()
                {
                    Aloe::Types::Tuple<> t;
                    return ((*(get())).*meth)( t );
                }

#define ALOE_PP_MethodCaller__Tuple( N ) \
                template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) > \
                    R operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, )) \
                    {\
                        Aloe::Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) >t \
                            ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, )); \
                            return ((*(get())).*meth)( t ); \
                    }

                ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, MethodCaller__Tuple );

            };
        
        
        template< class Interface, class R >
            struct MethodCaller< Interface, R, R (Interface::*)( const Aloe::Types::None & ) > : Aloe::Utils::SmartPtr< Interface > 
            {
                typedef R (Interface::*Meth)( const Aloe::Types::None & );
                Meth meth;

                MethodCaller( Meth m, const Aloe::Utils::SmartPtr< Interface > &p )
                    : meth( m )
                    , Aloe::Utils::SmartPtr< Interface >( p )
                {
                }

                R operator () ()
                {
                    Aloe::Types::None n;
                    return ((*(get())).*meth)( n );
                }
            };

        


        template< class Interface, class ReferenceType >
            ReferenceType
            make_property( const Utils::SmartPtr< Interface > &ptr, ReferenceType property( const Utils::SmartPtr< Interface > & ))
            {
                return property( ptr );
            }
        
        template< class Ptr, class Interface, class ReferenceType >
            ReferenceType
            make_property( const Ptr &ptr, ReferenceType property( const Utils::SmartPtr< Interface > & ))
            {
                Utils::SmartPtr< Interface > p;
                if ( !p.QueryFrom( ptr ))
                {
                    throw Errors::InterfaceNotFound< Interface >();
                }
                    
                return property( p );
            }

#define ALOE_PP_make_property__definition( N ) \
        template< class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) > \
            make_property( const Utils::SmartPtr< Interface > &ptr, R (Interface::*property)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) ) \
            {\
                return Detail::MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) >( property, ptr );\
            } \
        template< class Ptr, class Interface, class R ALOE_PP_TEMPLATE_R( N, COMMA, COMMA, class, A,, ) > \
            MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) > \
            make_property( const Ptr &ptr, R (Interface::*property)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, )) ) \
            {\
                Utils::SmartPtr< Interface > p; \
                if ( !p.QueryFrom( ptr )) \
                { \
                    throw Errors::InterfaceNotFound< Interface >(); \
                } \
                return Detail::MethodCaller< Interface, R, R (Interface::*)( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A,, ) ) >( property, p ); \
            }
        
        ALOE_PP_make_property__definition( 0 );
        ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, make_property__definition );
        
    };//Detail
    
    inline Types::Identifier GetIdOfName( const Types::String &csName );
    
    struct IProvider
    {
        aloe__iid__const( IProvider, 0x2 );
        
        virtual Aloe::Types::Bool Query( const Aloe::Types::Identifier &iid, Aloe::Types::RawPointer &ptr, Aloe::IRefCount * &pCount ) = 0;
        virtual Aloe::Types::Bool QueryCounterAddRef( Aloe::IRefCount * &pCount ) = 0;
    };
    
    aloe__interface( IIdentifierFactory )
    {
        aloe__iid__const( IIdentifierFactory, 0x1 );

        virtual Types::Identifier getIdOfName( const Types::String &csName ) = 0;
    };
    
    extern Utils::SmartPtr< IProvider > Root;

    inline Types::Identifier GetIdOfName( const Types::String &csName )
    {
        static Utils::SmartPtr< IIdentifierFactory > factory;
        
        if ( !factory )
        {
            factory.QueryFrom( Root );
        }

        return factory->getIdOfName( csName );
    }
    
    
    aloe__interface( IEvent )
    {
        aloe__iid__const( IEvent, 0x3 );
        
        aloe__method( IEvent, Invoke
                , type( Bool )
                , arg( listener, In, pointer( IProvider ))
                );
    };
    
    struct IEventSource;

    namespace Detail {
    
        struct Event
        {
            Utils::SmartPtr< IEventSource > obj;

            Event( const Utils::SmartPtr< IEventSource > &o ) : obj ( o )
            {
            }
            
            template< class Interface, class Args >
                struct Proxy : Utils::SmartPtr< IEventSource >
                {
                    typedef Types::Bool (Interface::*Meth)( const Args & );
                    Meth meth;
                    
                    Proxy( const Event &e, Meth m ) : Utils::SmartPtr< IEventSource >( e.obj ), meth( m )
                    {
                    }

                    Types::None Call( const Args &args );

#define ALOE_PP_Event__Proxy__call( N ) \
                    template< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, class, A, a, ) >  \
                        Types::None operator () ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, byConstReference, A, a, ) ) \
                        { \
                            return Call( Types::Tuple< ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getClass, A, a, ) > \
                                    ( ALOE_PP_TEMPLATE_R( N, NONE, COMMA, getValue, A, a, ) )); \
                        }
                
                    ALOE_PP_GENERATE_MAX( NONE, SEMICOLON, Event__Proxy__call );

                };
            
            template< class Interface, class Args >
                Proxy< Interface, Args >
                operator [] ( Types::Bool (Interface::*event)( const Args & ) )
                {
                    return Proxy< Interface, Args >( *this, event );
                }
        };
    
    };//Detail
    
    
    aloe__interface( IEventSource )
    {
        aloe__iid__const( IEventSource, 0x4 );
    
        aloe__prop( IEventSource, Listeners
                , ____, ____
                , ____, ____, ____
                , append, type( Bool ), pointer( IProvider )
                , remove, type( Bool ), pointer( IProvider )
                , ____, ____, ____ );
    
        aloe__method( IEventSource, RaiseEvent
                , ____
                , arg( event, In, pointer( IEvent ))
                );

        static Detail::Event Raise( const Utils::SmartPtr< IEventSource > &src )
        {
            return Detail::Event( src );
        }

    };

    aloe__interface( IStringsDictionary )
    {
        aloe__iid__const( IStringsDictionary, 0x5 );
        
        aloe__prop( IStringsDictionary, String
                , map , type( String )
                , get , put , type( String )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    
    };
    
    aloe__interface( IStringEncoding )
    {
        aloe__iid__const( IStringEncoding, 0x6 );
    
        aloe__method( IStringEncoding, ReadString
                , type( String )
                , arg( encoded, In, type( CStr ))
                );
    
        aloe__method( IStringEncoding, WriteString
                , type( Long )
                , tuple2( 
                    arg( buffer, Out, type( NCStr )),
                    arg( text, In, type( String ))
                    )
                );
    };

    aloe__interface( IStringBuilder )
    {
        aloe__iid__const( IStringBuilder, 0x7 );
        
        aloe__prop( IStringBuilder, StringsDictionary
                , map , type( CStr )
                , get , put , pointer( IStringsDictionary )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
        
        aloe__prop( IStringBuilder, StringEncoding
                , map , type( CStr )
                , get , put , pointer( IStringEncoding )
                , ____, ____, ____
                , ____, ____, ____
                , ____, ____, ____ );
    
    };

    namespace Detail {

        struct CRefCount : virtual IRefCount, virtual IProvider
        {
            Types::Long   m_iCount;

            CRefCount() : m_iCount(1)
            {
            }

            virtual ~CRefCount()
            {
            }

            Utils::SmartPtr<> __self__()
            {
                return Utils::SmartPtr<>( this, this ).AddRef();
            }
            
            void AddRef()
            {
                ++m_iCount;
            }

            Types::Bool RemRef()
            {
                if ( 0 == --m_iCount )
                {
                    delete this;
                    return true;
                }
                return false;
            }

            aloe__Query_impl( 0, (), 0, () );
            
        };
        
        template< class Interface, class Args > struct CMethodCall : IEvent, CRefCount
        {
            typedef Types::Bool (Interface::*Meth)( const Args & );
            Meth meth;
            Args args;

            CMethodCall( Meth m, const Args &a ) : meth( m ), args( a )
            {
            }

            Types::Bool Invoke( const Utils::SmartPtr< IProvider > &ptr )
            {
                Utils::SmartPtr< Interface > listener;
                if ( listener.QueryFrom( ptr ))
                {
                    return ((*listener).*meth)( args );
                }
                return true;
            }
        
            aloe__Query_impl( 1, ( IEvent ), 0, () );
            
        };
        
        template< class Interface, class Args, class B >
            Utils::SmartPtr< IEvent > make_method_call( Types::Bool (Interface::*meth)( const Args & ), const B &args )
            {
                CMethodCall< Interface, Args > *ptr = new CMethodCall< Interface, Args >( meth, args );
                return Utils::SmartPtr< IEvent >( ptr, ptr );
            }

        template< class Interface, class Args >
            Types::None Event::Proxy< Interface, Args >::Call( const Args &args )
            {
                return get()->RaiseEvent( make_method_call( meth, args ));
            }

        //
        //
        // Automatic implementation of Query and QueryCounterAddRef
        //
        //
        
        template< const int N > struct NoType
        {
        };

        template< class IType > struct Interface : virtual IType
        {
            inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                if ( aloe__iid_of( IType ) == iid )
                {
                    reinterpret_cast< IType *&>( argPtr ) = this;
                    return true;
                }
                else {
                    return false;
                }
            }
        };

        template< const int N > struct Interface< NoType< N > >
        {
            inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
            {
                return false;
            }
        };
        
        template< class A1 = NoType< 1 >, class A2 = NoType< 2 >, class A3 = NoType< 3 >, class A4 = NoType< 4 >
            , class A5 = NoType< 5 >, class A6 = NoType< 6 >, class A7 = NoType< 7 >, class A8 = NoType< 8 > >
            struct Bases : A1, A2, A3, A4, A5, A6, A7, A8
            {
            };
        
        template< class A1 = NoType< 1 >, class A2 = NoType< 2 >, class A3 = NoType< 3 >, class A4 = NoType< 4 >
            , class A5 = NoType< 5 >, class A6 = NoType< 6 >, class A7 = NoType< 7 >, class A8 = NoType< 8 > >
            struct Interfaces : Interface< IProvider >, Interface< A1 >, Interface< A2 >, Interface< A3 >, Interface< A4 >
				, Interface< A5 >, Interface< A6 >, Interface< A7 >, Interface< A8 >
            {
                inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
                {
                    return  Interface< A1 >::Query( iid, argPtr, argCount ) ||
                            Interface< A2 >::Query( iid, argPtr, argCount ) ||
                            Interface< A3 >::Query( iid, argPtr, argCount ) ||
                            Interface< A4 >::Query( iid, argPtr, argCount ) ||
                            Interface< A5 >::Query( iid, argPtr, argCount ) ||
                            Interface< A6 >::Query( iid, argPtr, argCount ) ||
                            Interface< A7 >::Query( iid, argPtr, argCount ) ||
                            Interface< A8 >::Query( iid, argPtr, argCount ) ||
                            Interface< IProvider >::Query( iid, argPtr, argCount );
                }
            };

        template< class Type, class Interfaces, class Bases >
            struct Implementation : virtual Interfaces, Bases
            {
                Types::Bool QueryCounterAddRef( IRefCount * &pCount )
                {
                    pCount = add_ref( this );
                    return (0 != pCount);
                }

                inline Types::Bool Query( const Types::Identifier &iid, Types::RawPointer &argPtr, IRefCount * &argCount )
                {
                    if ( Interfaces::Query( iid, argPtr, argCount ) || Bases::Query( iid, argPtr, argCount ))
                    {
                        argCount = add_ref( this );
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            };

    };//Detail

}; //Aloe

#pragma warning(default:4250)

#endif//ALOE_INCLUDED_ALOE_H
