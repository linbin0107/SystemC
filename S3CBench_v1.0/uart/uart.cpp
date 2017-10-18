//========================================================================================
//
// File Name    : tb_uart.h
// Description  : Testbench
// Release Date : 02/12/2014
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Nandeesh Veeranna
//
// Revision History
//---------------------------------------------------------------------------------------
// Date         Version    Author      Description
//---------------------------------------------------------------------------------------
//14/02/2013      1.0       PolyU    UART main description
//22/07/2016      1.1     PolyU DARC Lab    Modified for Hardaware Trojan case  
//=======================================================================================

#include "uart.h"
#include "define.h"
void uart::uart_main(void)
{
    bool flag;
    //local variables

    sc_uint<8> r_data_buff, t_data_buff;
    bool rx_buff, tx_buff;
    bool trans_flag, recv_flag;
    bool rx_flag, tx_flag, active, busy_flag;
    int i, j, p, cnt = 0, count1;
    trans_flag = 0;
    recv_flag = 0;
    tx_flag = 0;
    rx_flag = 0;
    r_data_buff = "00000000";
    t_data_buff = "11111111";
    active = 0;
    sc_uint<4> k;
    //wait for reset
    sc_uint<8> count = 0;
    wait();

    while (true) {
        while (!active) //wait_until(active == 1)
        {
            if (cnt == 10416) //9600 baudrate
            {
                active = 1;
                cnt = 0;
            }

            else {
                active = 0;
                cnt += 1;
            }

            if (!tx_flag && t_ack.read() == 1) //get transmit signal
            {
                tx_flag = 1;
                t_data_buff = t_data.read();
                cout << endl
                     << t_data_buff << endl;
            }

            if (rx_flag == 1) //clear receiving signal
            {
                rx_flag = 0;
                r_ack.write(rx_flag);
            }
        }

        /************************************************************/
        /***************** Receiving Operation ********************/
        /************************************************************/

        rx_buff = rx.read();
        if (rx_buff == STARTBIT && !recv_flag) {
            busy_flag = 1;
            recv_flag = 1;
            i = 0;
        } // Wait for recieved start-bit

        else if (recv_flag == 1 && i != WORDLEN) {
/*----- Sequential With Memory Trojan(Type1) ----- */

/*----- Delay the service and also missing of intermediate data ----- */

#if defined(SWM1) || defined(SWM1_TRI) //The Trojan sustains forever when it is triggered

            if (count >= 50) { // replace it with lesser count value (for Eg. count>=19) to know the Trojan effect
                flag = 1;
                //break;
            }
            if (flag == 1) {
                wait(); flag=0;
            }
/*----- Sequential With Memory Trojan(Type2) ----- */
#elif defined(SWM2) || defined(SWM2_TRI) // The Trojan is active for a particular duration when triggered

            if (count == 35) {   //replace it with lesser count value (Eg. count==6) to know the Trojan effect

                flag = 1;
            }
            else if (count == 40) { //replace it with lesser count value (Eg. count==12) to know the Trojan effect
                flag = 0;
            }
            if (flag == 1) {
                wait();
            }

#endif
            r_data_buff[i] = rx_buff;
            i++;
        } // store recived data into buffer once start-bit is dectected

        else if (recv_flag && i == WORDLEN) {
            if (rx_buff == STOPBIT) {
                r_data.write(r_data_buff);
                rx_flag = 1;
                count++;
                r_ack.write(rx_flag);
            }
            busy_flag = 0;
            recv_flag = 0;
        } // data is output when stop-bit is recieved, otherwise abandon it

        else {
            busy_flag = 0;
            recv_flag = 0;
            i = 0;
        }
        /************************************************************/
        /**************** Transmitting Operation ******************/
        /************************************************************/
        if (!tx_flag && (t_ack.read() == 1)) {
            tx_flag = 1;
            t_data_buff = t_data.read(); // get transmitting signal
        }

        if (tx_flag && !trans_flag) { // transmitting starts and sending start-bit
            j = 0;
            trans_flag = 1;
            tx_buff = STARTBIT;
            tx.write(tx_buff);
        }

        else if (trans_flag && j != WORDLEN) { // sending transmitted data
            tx_buff = t_data_buff[j];
            tx.write(tx_buff);
            j++;
        }

        else if (trans_flag && j == WORDLEN) { // transmitting ends and sending stop-bit
            trans_flag = 0;
            tx_flag = 0;
            j = 0;
            tx_buff = STOPBIT;
            tx.write(tx_buff);
            //active=0;
            //wait();
        }

        else {
            trans_flag = 0;
            tx_flag = 0;
            j = 0;
        }

        wait();
    }
}




























