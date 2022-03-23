#include "core_http_client.h"
#include "using_mbedtls.h"
#include "http_demo_utils.h"

#ifndef democonfigROOT_CA_PEM
    #error "Please define democonfigROOT_CA_PEM in demo_config.h."
#endif
#ifndef democonfigHTTPS_PORT
    #define democonfigHTTPS_PORT    ( 443 )
#endif

/* Check that a transport timeout for transport send and receive is defined. */
#ifndef democonfigTRANSPORT_SEND_RECV_TIMEOUT_MS
    #define democonfigTRANSPORT_SEND_RECV_TIMEOUT_MS    ( 5000 )
#endif

/* Check that a size for the user buffer is defined. */
#ifndef democonfigUSER_BUFFER_LENGTH
    #define democonfigUSER_BUFFER_LENGTH    ( 4096 )
#endif

/* Check that the range request length is defined. */
#ifndef democonfigRANGE_REQUEST_LENGTH
    #define democonfigRANGE_REQUEST_LENGTH    ( 2048 )
#endif

const TickType_t x1SecDelay = 1000 / portTICK_PERIOD_MS;
volatile uint32_t parseCount = 0;

int main(void) {
	xTaskCreate( parseCountry1DataTask, "c1t", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL )
	xTaskCreate( parseCountry2DataTask, "c2t", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL )
	xTaskCreate( parseCountry3DataTask, "c3t", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL )
	xTaskCreate( parseCountry4DataTask, "c4t", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL )
	xTaskCreate( parseCountry5DataTask, "c5t", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL )
	
	vTaskStartScheduler();
	for( ;; );
}

static void fetchJson(URL, data*){

	/* The transport layer interface used by the HTTP Client library. */
    TransportInterface_t xTransportInterface;
    /* The network context for the transport layer interface. */
    NetworkContext_t xNetworkContext = { 0 };
    PlaintextTransportParams_t xPlaintextTransportParams = { 0 };
    /* An array of HTTP paths to request. */
    const httpPathStrings_t xHttpMethodPaths[] =
    {
        { democonfigGET_PATH,  httpexampleGET_PATH_LENGTH  },
        { democonfigHEAD_PATH, httpexampleHEAD_PATH_LENGTH },
        { democonfigPUT_PATH,  httpexamplePUT_PATH_LENGTH  },
        { democonfigPOST_PATH, httpexamplePOST_PATH_LENGTH }
    };
    /* The respective method for the HTTP paths listed in #httpMethodPaths. */
    const httpMethodStrings_t xHttpMethods[] =
    {
        { HTTP_METHOD_GET,  httpexampleHTTP_METHOD_GET_LENGTH  },
        { HTTP_METHOD_HEAD, httpexampleHTTP_METHOD_HEAD_LENGTH },
        { HTTP_METHOD_PUT,  httpexampleHTTP_METHOD_PUT_LENGTH  },
        { HTTP_METHOD_POST, httpexampleHTTP_METHOD_POST_LENGTH }
    };
    BaseType_t xIsConnectionEstablished = pdFALSE;
    UBaseType_t uxHttpPathCount = 0U;

    /* The user of this demo must check the logs for any failure codes. */
    BaseType_t xDemoStatus = pdPASS;

    /* Remove compiler warnings about unused parameters. */
    ( void ) pvParameters;

    /* Set the pParams member of the network context with desired transport. */
    xNetworkContext.pParams = &xPlaintextTransportParams;

    /**************************** Connect. ******************************/

    /* Attempt to connect to the HTTP server. If connection fails, retry after a
     * timeout. The timeout value will be exponentially increased until either the
     * maximum number of attempts or the maximum timeout value is reached. The
     * function returns pdFAIL if the TCP connection cannot be established with
     * the server after the number of attempts. */
    xDemoStatus = connectToServerWithBackoffRetries( prvConnectToServer,
                                                     &xNetworkContext );

    if( xDemoStatus == pdPASS )
    {
        /* Set a flag indicating that a TCP connection has been established. */
        xIsConnectionEstablished = pdTRUE;

        /* Define the transport interface. */
        xTransportInterface.pNetworkContext = &xNetworkContext;
        xTransportInterface.send = Plaintext_FreeRTOS_send;
        xTransportInterface.recv = Plaintext_FreeRTOS_recv;
    }
    else
    {
        /* Log error to indicate connection failure after all
         * reconnect attempts are over. */
        LogError( ( "Failed to connect to HTTP server %.*s.",
                    ( int32_t ) httpexampleSERVER_HOSTNAME_LENGTH,
                    democonfigSERVER_HOSTNAME ) );
    }

    /*********************** Send HTTP request.************************/

    for( uxHttpPathCount = 0; 
         uxHttpPathCount < httpexampleNUMBER_HTTP_PATHS; 
         ++uxHttpPathCount )
    {
        if( xDemoStatus == pdPASS )
        {
            xDemoStatus = prvSendHttpRequest( 
                              &xTransportInterface,
                              xHttpMethods[ uxHttpPathCount ].pcHttpMethod,
                              xHttpMethods[ uxHttpPathCount ].ulHttpMethodLength,
                              xHttpMethodPaths[ uxHttpPathCount ].pcHttpPath,
                              xHttpMethodPaths[ uxHttpPathCount ].ulHttpPathLength );
        }
        else
        {
            break;
        }
    }

    /**************************** Disconnect. ******************************/

    /* Close the network connection to clean up any system resources that the
     * demo may have consumed. */
    if( xIsConnectionEstablished == pdTRUE )
    {
        /* Close the network connection.  */
        Plaintext_FreeRTOS_Disconnect( &xNetworkContext );
    }

    if( xDemoStatus == pdPASS )
    {
        LogInfo( ( "prvHTTPDemoTask() completed successfully. "
                   "Total free heap is %u.\r\n",
                   xPortGetFreeHeapSize() ) );
        LogInfo( ( "Demo completed successfully.\r\n" ) );
    }
}


static void parseCountry1DataTask( void *pvParameters ){
for( ;; )
    {
		if (parseCount % 5 != 0){
			vTaskDelay(x1SecDelay);
		} else {
		
		
		HTTPStatus_t HTTPClient_Send( const TransportInterface_t * pTransport,
                              HTTPRequestHeaders_t * pRequestHeaders,
                              const uint8_t * pRequestBodyBuf,
                              size_t reqBodyBufLen,
                              HTTPResponse_t * pResponse,
                              uint32_t sendFlags );
		
			parseCount++;
		}
	}
}

static void parseCountry2DataTask( void *pvParameters ){
for( ;; )
    {
		if (parseCount % 5 != 1){
			vTaskDelay(x1SecDelay);
		} else {
		
			parseCount++;
		}
	}
}

static void parseCountry3DataTask( void *pvParameters ){
for( ;; )
    {
		if (parseCount % 5 != 2){
			vTaskDelay(x1SecDelay);
		} else {
		
			parseCount++;
		}
	}
}

static void parseCountry4DataTask( void *pvParameters ){
for( ;; )
    {
		if (parseCount % 5 != 3){
			vTaskDelay(x1SecDelay);
		} else {
		
			parseCount++;
		}
	}
}

static void parseCountry5DataTask( void *pvParameters ){
for( ;; )
    {
		if (parseCount % 5 != 4){
			vTaskDelay(x1SecDelay);
		} else {
		
			parseCount++;
		}
	}
}