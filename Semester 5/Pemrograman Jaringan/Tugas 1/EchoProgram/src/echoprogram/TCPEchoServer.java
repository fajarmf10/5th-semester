/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package echoprogram;

import java.io.*;
import java.net.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 *
 * @author fajar
 */
public class TCPEchoServer {

    /**
     * @param args the command line arguments
     */
    
    private static ServerSocket serverSocket;
    private static final int PORT = 1234;

    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("Opening port…\n");
        try{
            serverSocket = new ServerSocket(PORT); //Step 1.
        }
        catch(IOException ioEx){
            System.out.println("Unable to attach to port!");
            System.exit(1);
        }
        do{
            handleClient();
        }while(true);
    }
    
    private static void handleClient(){
        Socket link = null; //Step 2
        try{
            link = serverSocket.accept(); //Step 2
            Scanner input = new Scanner(link.getInputStream()); //Step 3
            PrintWriter output = new PrintWriter(link.getOutputStream(), true); //Step 3.
            int numMessages = 0;
            String message = input.nextLine(); //Step 4.
//            DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
            DateFormat jam = new SimpleDateFormat("hh:mm:ss");
            DateFormat hari = new SimpleDateFormat("EEEE");
            DateFormat bulan = new SimpleDateFormat("MM");
            Date now = new Date();// EEE gives short day names, EEEE would be full length.
            
            while (!message.equals("!q")){
                if(message.equals("!t")){ //Jam
                    System.out.println("Klien mengambil jam.");
                    output.println("Jam :" + jam.format(now));
                    output.flush();
//                link.getOutputStream();
//                System.out.println(df.format(now));
                }
                else if(message.equals("!d")){
                    System.out.println("Klien mengambil hari.");
                    output.println(hari.format(now));
                    output.flush();
                }
                else if(message.equals("!m")){
                    System.out.println("Klien mengambil bulan.");
                    output.println(bulan.format(now));
                    output.flush();                    
                }
                else if(message.equals("!#")){
                    System.out.println("Klien nyari quote, hehe.");
                    output.println("The best love is the kind that awakens the soul; that makes us reach for more, that plants the fire in our hearts and brings peace to our minds. That's what I hope to give you forever.");
                    output.flush();
                }
                else if (message.equals("!id")){
                    System.out.println("Klien nyari data diri.");
                    output.println("Namamu");
                    output.flush();
                }
                else{
                    System.out.println("Message received.");
                    numMessages++;
                    output.println("Your #" + numMessages + " message(s) is: " + message); //Step 4.
                    }
                message = input.nextLine();
                }
            output.println(numMessages + " messages received."); //Step 4.
        }
        catch(IOException ioEx){
            ioEx.printStackTrace();
        }
        finally{
            try{
                System.out.println("\n* Closing connection… *");
                link.close(); //Step 5.
            }
            catch(IOException ioEx){
                System.out.println("Unable to disconnect!");
                System.exit(1);
            }
        }
    }
}
