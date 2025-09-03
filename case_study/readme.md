# 📚 Studi Kasus Stack

## A. Validasi Pasangan Bracket

### Deskripsi
Dalam ekspresi matematika atau program, sering digunakan tanda kurung seperti `()`, `[]`, dan `{}`.  
Setiap kurung yang dibuka harus memiliki pasangan kurung yang ditutup **dalam urutan yang benar**.  

Stack digunakan untuk menyelesaikan masalah ini karena sifatnya **Last In, First Out (LIFO)**.  
- Setiap kali menemukan kurung buka, kita simpan ke dalam stack.  
- Setiap kali menemukan kurung tutup, kita ambil elemen terakhir dari stack dan cek apakah pasangannya cocok.  
- Jika sampai akhir pengecekan stack kosong dan semua pasangan cocok, maka ekspresi valid.  
- Jika ada kurung yang tidak cocok atau urutan penutupannya salah, maka ekspresi tidak valid.  
