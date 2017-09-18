/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package echoprogram;
import java.io.*;
import java.net.*;
import java.util.*;

/**
 *
 * @author fajar
 */
public class TCPEchoClient {
    private static InetAddress host;
    private static final int PORT = 8228;
    public static void main(String[] args){
        try{
            host = InetAddress.getLocalHost();
        }
        catch(UnknownHostException uhEx){
            System.out.println("Host ID not found!");
            System.exit(1);
        }
        accessServer();
    }
    
    private static void accessServer(){
        Socket link = null; //Step 1.
        try{
            link = new Socket(host,PORT); //Step 1.
            Scanner input2 = new Scanner(link.getInputStream());
            Scanner input = new Scanner(link.getInputStream()); //Step 2.
            PrintWriter output = new PrintWriter(link.getOutputStream(),true); //Step 2.
        
        //Set up stream for keyboard entry…
        Scanner userEntry = new Scanner(System.in);
        String message, response;
        do{
            System.out.print("Enter message: ");
            message = userEntry.nextLine();
            if(message.equals("!id")) {
                System.out.print("Masukkan ID >  ");
                String id = input2.nextLine();
                output.println(output);
            }
            output.println(message); //Step 3.
            response = input.nextLine(); //Step 3.
            System.out.println("\nSERVER> "+response);
        }while (!message.equals("!q"));
        }
        catch(IOException ioEx){
            ioEx.printStackTrace();
        }
        finally{
            try{
                System.out.println("\n* Closing connection… *");
                link.close(); //Step 4.
            }
            catch(IOException ioEx){
                System.out.println("Unable to disconnect!");
                System.exit(1);
            }
        }
    }
}
