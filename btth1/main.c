
#include <stdio.h>
#include <string.h>

#define MAX_NV 50

// Khai bao cau truc nhan vien
struct NhanVien {
    int maNV;
    char hoTen[50];
    int soPhutDiMuon;
    float luongCoBan;
};

// Khai bao nguyen mau ham
int timTheoMaNV(struct NhanVien ds[], int soLuong, int maNV);
int themNhanVien(struct NhanVien ds[], int soLuong);
void hienThiDanhSach(struct NhanVien ds[], int soLuong);
void capNhatPhutDiMuon(struct NhanVien ds[], int soLuong);
void timKiemNhanVien(struct NhanVien ds[], int soLuong);
void xoaBoDem(void);
int nhapSoNguyen(const char thongBao[], int *giaTri);
int nhapSoThuc(const char thongBao[], float *giaTri);

int main(void) {
    struct NhanVien ds[MAX_NV];
    int soLuong = 0;
    int luaChon;

    do {
        printf("\n===== HE THONG QUAN LY CHAM CONG HRM =====\n");
        printf("1. Them nhan vien moi\n");
        printf("2. Hien thi danh sach va tinh luong\n");
        printf("3. Cap nhat so phut di muon\n");
        printf("4. Tim kiem nhan vien theo ma\n");
        printf("0. Thoat\n");
        printf("==========================================\n");

        if (!nhapSoNguyen("Nhap lua chon: ", &luaChon)) {
            printf("Du lieu khong hop le. Vui long chon lai!\n");
            continue;
        }

        switch (luaChon) {
            case 1:
                soLuong = themNhanVien(ds, soLuong);
                break;

            case 2:
                hienThiDanhSach(ds, soLuong);
                break;

            case 3:
                capNhatPhutDiMuon(ds, soLuong);
                break;

            case 4:
                timKiemNhanVien(ds, soLuong);
                break;

            case 0:
                printf("Da thoat chuong trinh!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (luaChon != 0);

    return 0;
}

// Xoa phan du con lai trong bo dem nhap
void xoaBoDem(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        // Doc bo ky tu con lai
    }
}

// Nhap so nguyen
int nhapSoNguyen(const char thongBao[], int *giaTri) {
    printf("%s", thongBao);

    if (scanf("%d", giaTri) != 1) {
        xoaBoDem();
        return 0;
    }

    xoaBoDem();
    return 1;
}

// Nhap so thuc
int nhapSoThuc(const char thongBao[], float *giaTri) {
    printf("%s", thongBao);

    if (scanf("%f", giaTri) != 1) {
        xoaBoDem();
        return 0;
    }

    xoaBoDem();
    return 1;
}

// Tim nhan vien theo ma, tra ve vi tri hoac -1
int timTheoMaNV(struct NhanVien ds[], int soLuong, int maNV) {
    int i;

    for (i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }

    return -1;
}

// Them nhan vien moi
int themNhanVien(struct NhanVien ds[], int soLuong) {
    struct NhanVien nv;
    int viTri;
    int doDai;

    if (soLuong >= MAX_NV) {
        printf("Danh sach da day, khong the them nhan vien!\n");
        return soLuong;
    }

    if (!nhapSoNguyen("Nhap ma nhan vien: ", &nv.maNV)) {
        printf("Ma nhan vien khong hop le!\n");
        return soLuong;
    }

    if (nv.maNV <= 0) {
        printf("Ma nhan vien phai lon hon 0!\n");
        return soLuong;
    }

    viTri = timTheoMaNV(ds, soLuong, nv.maNV);

    if (viTri != -1) {
        printf("Ma nhan vien da ton tai!\n");
        return soLuong;
    }

    printf("Nhap ho va ten: ");

    if (fgets(nv.hoTen, sizeof(nv.hoTen), stdin) == NULL) {
        printf("Loi khi nhap ho ten!\n");
        return soLuong;
    }

    doDai = (int)strlen(nv.hoTen);

    if (doDai > 0 && nv.hoTen[doDai - 1] == '\n') {
        nv.hoTen[doDai - 1] = '\0';
    } else {
        xoaBoDem();
    }

    if (strlen(nv.hoTen) == 0) {
        printf("Ho ten khong duoc de trong!\n");
        return soLuong;
    }

    if (!nhapSoNguyen("Nhap so phut di muon: ",
                      &nv.soPhutDiMuon)) {
        printf("So phut di muon khong hop le!\n");
        return soLuong;
    }

    if (nv.soPhutDiMuon < 0) {
        printf("So phut di muon khong duoc am!\n");
        return soLuong;
    }

    if (!nhapSoThuc("Nhap luong co ban: ", &nv.luongCoBan)) {
        printf("Luong co ban khong hop le!\n");
        return soLuong;
    }

    if (nv.luongCoBan < 0) {
        printf("Luong co ban khong duoc am!\n");
        return soLuong;
    }

    ds[soLuong] = nv;
    soLuong++;

    printf("Them nhan vien thanh cong!\n");

    return soLuong;
}

// Hien thi danh sach va tinh luong thuc nhan
void hienThiDanhSach(struct NhanVien ds[], int soLuong) {
    int i;
    int tienPhat;
    float luongThucNhan;

    if (soLuong == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }

    printf("\n--- DANH SACH NHAN VIEN ---\n");
    printf("%-8s | %-25s | %-10s | %-18s\n",
           "Ma NV", "Ho ten", "Phut muon", "Luong thuc nhan");

    for (i = 0; i < soLuong; i++) {
        if (ds[i].soPhutDiMuon > 15) {
            tienPhat = 50000;
        } else {
            tienPhat = 0;
        }

        luongThucNhan = ds[i].luongCoBan - tienPhat;

        printf("%-8d | %-25s | %-10d | %.0f VND\n",
               ds[i].maNV,
               ds[i].hoTen,
               ds[i].soPhutDiMuon,
               luongThucNhan);
    }
}

// Cap nhat so phut di muon
void capNhatPhutDiMuon(struct NhanVien ds[], int soLuong) {
    int maNV;
    int soPhutMoi;
    int viTri;

    if (soLuong == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }

    if (!nhapSoNguyen("Nhap ma NV can cap nhat: ", &maNV)) {
        printf("Ma nhan vien khong hop le!\n");
        return;
    }

    viTri = timTheoMaNV(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien!\n");
        return;
    }

    if (!nhapSoNguyen("Nhap so phut di muon moi: ",
                      &soPhutMoi)) {
        printf("So phut nhap vao khong hop le!\n");
        return;
    }

    if (soPhutMoi < 0) {
        printf("So phut di muon khong duoc am!\n");
        return;
    }

    ds[viTri].soPhutDiMuon = soPhutMoi;

    printf("=> Cap nhat thanh cong!\n");
}

// Tim kiem va hien thi thong tin nhan vien
void timKiemNhanVien(struct NhanVien ds[], int soLuong) {
    int maNV;
    int viTri;
    int tienPhat;
    float luongThucNhan;

    if (soLuong == 0) {
        printf("Danh sach nhan vien dang rong!\n");
        return;
    }

    if (!nhapSoNguyen("Nhap ma NV can tim: ", &maNV)) {
        printf("Ma nhan vien khong hop le!\n");
        return;
    }

    viTri = timTheoMaNV(ds, soLuong, maNV);

    if (viTri == -1) {
        printf("Khong tim thay nhan vien!\n");
        return;
    }

    if (ds[viTri].soPhutDiMuon > 15) {
        tienPhat = 50000;
    } else {
        tienPhat = 0;
    }

    luongThucNhan = ds[viTri].luongCoBan - tienPhat;

    printf("\n--- THONG TIN NHAN VIEN ---\n");
    printf("Ma nhan vien: %d\n", ds[viTri].maNV);
    printf("Ho ten: %s\n", ds[viTri].hoTen);
    printf("So phut di muon: %d\n", ds[viTri].soPhutDiMuon);
    printf("Luong co ban: %.0f VND\n", ds[viTri].luongCoBan);
    printf("Tien phat: %d VND\n", tienPhat);
    printf("Luong thuc nhan: %.0f VND\n", luongThucNhan);
}