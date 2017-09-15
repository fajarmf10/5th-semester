package com.example.sosispanggang.lala;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private EditText edtNilai;
    private Button btnCheck;
    private TextView ala;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final EditText edtNilai = (EditText)findViewById(R.id.editText);
        Button btnCheck = (Button)findViewById(R.id.lala);
        final TextView ala = (TextView)findViewById(R.id.ala);

        btnCheck.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View view) {
                final String nilai = edtNilai.getText().toString();
                final Integer nilai1 = Integer.parseInt(nilai);

                if (nilai1 >= 81 && nilai1 <= 100){
                 ala.setText("A");
                }
                else if(nilai1<= 80 && nilai1 >=71){
                    ala.setText("AB");
                }
                else if(nilai1 <71 && nilai1 >65){
                    ala.setText("B");
                }
                else if(nilai1 <66 && nilai1 >=60){
                    ala.setText("BC");
                }
                else if(nilai1 <60 && nilai1 >=40){
                    ala.setText("D");
                }
                else ala.setText("E");
            }
        });

        }



//    edtPanjang = (EditText)findViewById(R.id.edt_panjang);
//    edtLebar = (EditText)findViewById(R.id.edt_lebar);
//    btnHitung = (Button)findViewById(R.id.btn_hitung);
//    txtLuas = (TextView)findViewById(R.id.txt_luas);
//
//        btnHitung.setOnClickListener(new View.OnClickListener() {
//        @Override
//        public void onClick(View view) {
//            double luas = 0;    //inisialisasi luas = 0
//            String panjang, lebar;
//
//            if(checkNilai()){
//                panjang = edtPanjang.getText().toString().trim();
//                lebar = edtLebar.getText().toString().trim();
//                double p = Double.parseDouble(panjang);
//                double l = Double.parseDouble(lebar);
//
//                luas = p * l;
//            }
//            else{
//                Snackbar snackbar1 = Snackbar.make(view, view.getResources().getString(R.string.hayoo), Snackbar.LENGTH_LONG);
//                snackbar1.show();//Snackbar error kosong
//            }
//
//            txtLuas.setText("Luas : "+luas);
//        }
//    });
//
//
//    private boolean checkNilai(){
//        if(edtLebar.getText().toString().equalsIgnoreCase("") || edtLebar.getText().toString().equalsIgnoreCase(".") || edtPanjang.getText().toString().equalsIgnoreCase("") || edtPanjang.getText().toString().equalsIgnoreCase("."))
//            return false;
//        else return true;
//    }

}
