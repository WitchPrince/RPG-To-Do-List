# RPG To-Do List

RPG To-Do List, günlük görev yönetimini bir Rol Yapma Oyunu (RPG) mekaniğine dönüştüren, terminal tabanlı (CLI) bir verimlilik uygulamasıdır. Kullanıcının tamamladığı görevler karşılığında deneyim puanı (EXP) ve oyun içi para birimi kazandığı, bu kazançlarla sanal bir marketten ürünler satın alabildiği bir ekosistem sunar.

## Proje Hakkında

Bu proje, karmaşık arayüzlere veya ağır kütüphanelere ihtiyaç duymadan, en temel bilgisayar bileşeni olan terminal üzerinde çalışan sürdürülebilir bir oyunlaştırma (gamification) aracıdır. C programlama dili ile geliştirilen uygulama, minimum sistem kaynağı tüketimi ve maksimum taşınabilirlik ilkesiyle tasarlanmıştır.

## Temel Özellikler

Uygulama modüler bir yapıya sahiptir ve aşağıdaki temel sistemleri içerir:

### 1. Görev Yönetim Sistemi (Quest System)
* **Görev Ekleme:** Kullanıcılar görev adı, zorluk seviyesi (1-5), ödül miktarı ve detaylı açıklamalar ile yeni görevler oluşturabilir.
* **Otomatik Ödül Hesaplama:** İstenirse, zorluk seviyesine bağlı olarak ödül (Gold) ve EXP miktarı sistem tarafından otomatik hesaplanabilir.
* **Görev Tamamlama:** Tamamlanan görevler listelenir, ödüller kullanıcının bakiyesine eklenir ve görev "Tamamlanmış Görevler" veritabanına taşınır.
* **Düzenleme ve Silme:** Mevcut görevlerin parametreleri (ad, zorluk, ödül vb.) sonradan değiştirilebilir veya görevler tamamen silinebilir.

### 2. Market ve Ekonomi Sistemi
* **Dinamik Market:** Kullanıcılar kazandıkları paralar ile marketten ürün satın alabilirler.
* **Market Yönetimi:** Markete yeni ürün ekleme, fiyat güncelleme veya ürün kaldırma işlemleri yapılabilir.
* **Envanter Entegrasyonu:** Satın alınan ürünler otomatik olarak kullanıcı envanterine aktarılır ve bakiyeden düşülür.

### 3. Envanter Yönetimi
* **Eşya Görüntüleme:** Kullanıcı sahip olduğu eşyaları, miktarlarını ve detaylarını listeleyebilir.
* **Eşya Kullanımı:** Envanterdeki eşyalar "kullanılabilir" ve kullanıldığında envanterden eksilir.

### 4. Veri Kalıcılığı (Database)
* Tüm veriler (görevler, envanter, market, tamamlanan işler) yerel metin dosyalarında (`.txt`) saklanır. Bu sayede uygulama kapatılıp açıldığında veriler korunur.

## Gelecek Hedefleri

Projenin geliştirilme sürecinde aşağıdaki özelliklerin sisteme entegre edilmesi planlanmaktadır:

* **XP ve Seviye Sistemi:** Mevcut deneyim puanı kazanımının, dinamik bir seviye atlama (Level Up) mekaniğine dönüştürülmesi.
* **Kullanıcı Yönetimi:** Çoklu kullanıcı desteği ve giriş paneli (User Menu) eklenmesi.
* **Gömülü Sistem Desteği:** Yazılımın optimize edilerek ESP-32 gibi mikrodenetleyiciler ve geliştirme kartları üzerinde çalıştırılabilir hale getirilmesi.

## Teknik Detaylar ve Taşınabilirlik

Bu projenin en önemli teknik hedefi **bağımlılıksız (dependency-free)** yapısıdır.

* **Dil ve Standart:** Proje **C99** standartlarına uygun olarak geliştirilmiştir.
* **Kütüphaneler:** Sadece standart C kütüphaneleri (`stdio.h`, `stdlib.h`, `string.h`, `stdbool.h`) kullanılmıştır. Herhangi bir üçüncü parti framework veya harici kütüphane gerektirmez.
* **Platform:** GNU/Linux ve UNIX tabanlı sistemlerde (macOS dahil), GCC derleyicisi bulunan her terminal ortamında doğrudan derlenip çalıştırılabilir. Sistem kaynaklarını minimum düzeyde kullanır.

## Kurulum ve Kullanım

Projeyi derlemek ve sisteminize kurmak için proje dizininde bir terminal açarak aşağıdaki komutları kullanabilirsiniz.

### Derleme
Projeyi derlemek ve çalıştırılabilir `rpg` dosyasını oluşturmak için:

```bash
make all
```

### Kurulum (Sistem Geneli)
Uygulamayı sisteminize kurarak terminalin herhangi bir yerinden `rpg` komutu ile çağırmak için:

```bash
make install
```

### Temizleme
Derleme sonucu oluşan dosyaları temizlemek için:

```bash
make clean
```

## Geliştirme Süreci ve Yapay Zeka Bildirimi

Bu projenin mimari tasarımı, algoritma kurgusu, dosya yönetim sistemi ve mantıksal akışı tamamen geliştirici tarafından manuel olarak oluşturulmuştur.

**Yapay Zeka (AI) Kullanımı Hakkında:**
Projenin geliştirilme sürecinde Yapay Zeka araçlarından **yalnızca hata ayıklama (debugging)**, sözdizimi hatalarının tespiti ve derleyici uyarılarının giderilmesi amacıyla faydalanılmıştır. Kodun temel yapısı ve işleyiş mantığı üzerinde AI tarafından üretim yapılmamıştır.

## Lisans

Bu proje açık kaynaklıdır ve eğitim/geliştirme amacıyla özgürce kullanılabilir.
