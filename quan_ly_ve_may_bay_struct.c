#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;
    float baggageWeight;
    float baggageFee;
};

int main() {
    struct FlightTicket danhSachVe[100];

    int soLuong = 0;
    int luaChon;

    char pnrInput[15];
    int ticketClassInput;
    float baggageWeightInput;

    do {
        /* ==========================================
           MENU
           ========================================== */

        printf("\n");
        printf("===============================================\n");
        printf(" HE THONG BAN VE VA CHECK-IN MAY BAY\n");
        printf("===============================================\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve may bay\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("===============================================\n");

        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);

        switch (luaChon) {

            /* ======================================
               CASE 1: THEM VE
               ====================================== */

            case 1: {
                if (soLuong >= 100) {

                    printf("Danh sach ve da day, khong the them moi!\n");

                } else {

                    printf("\n--- THEM VE MAY BAY MOI ---\n");

                    printf("Nhap ma PNR: ");

                    scanf("%14s",
                          danhSachVe[soLuong].pnrCode);

                    /*
                     * Xoa ky tu '\n' sau scanf()
                     * truoc khi dung fgets().
                     */
                    while (getchar() != '\n');

                    printf("Nhap ho ten hanh khach: ");

                    fgets(
                        danhSachVe[soLuong].passengerName,
                        sizeof(danhSachVe[soLuong].passengerName),
                        stdin
                    );

                    /*
                     * Xoa '\n' o cuoi chuoi.
                     */
                    danhSachVe[soLuong].passengerName[
                        strcspn(
                            danhSachVe[soLuong].passengerName,
                            "\n"
                        )
                    ] = '\0';

                    printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                    scanf("%d", &ticketClassInput);

                    /*
                     * Kiem tra hang ve.
                     */
                    while (ticketClassInput < 1 ||
                           ticketClassInput > 3) {

                        printf("Hang ve khong hop le! "
                               "Vui long nhap 1, 2 hoac 3: ");

                        scanf("%d", &ticketClassInput);
                    }

                    danhSachVe[soLuong].ticketClass =
                        ticketClassInput;

                    printf("Nhap khoi luong hanh ly (kg): ");
                    scanf("%f", &baggageWeightInput);

                    /*
                     * Khong cho phep trong luong am.
                     */
                    while (baggageWeightInput < 0) {

                        printf("Khoi luong hanh ly khong hop le! "
                               "Vui long nhap lai: ");

                        scanf("%f", &baggageWeightInput);
                    }

                    danhSachVe[soLuong].baggageWeight =
                        baggageWeightInput;

                    /* Tinh phi hanh ly */

                    if (danhSachVe[soLuong].ticketClass == 3) {

                        /*
                         * Business duoc mien phi hanh ly.
                         */
                        danhSachVe[soLuong].baggageFee = 0.0f;

                    } else if (
                        danhSachVe[soLuong].baggageWeight <= 7.0f
                    ) {

                        danhSachVe[soLuong].baggageFee = 0.0f;

                    } else {

                        danhSachVe[soLuong].baggageFee =
                            (danhSachVe[soLuong].baggageWeight - 7.0f)
                            * 50000.0f;
                    }

                    printf(
                        "=> Them ve thanh cong! "
                        "Cuoc phat hanh ly qua can: %.0f VND.\n",
                        danhSachVe[soLuong].baggageFee
                    );

                    soLuong++;
                }

                break;
            }

            /* ======================================
               CASE 2: HIEN THI DANH SACH
               ====================================== */

            case 2: {

                if (soLuong == 0) {

                    printf("Danh sach ve dang rong!\n");

                } else {

                    printf("\n");
                    printf("========================================================================================\n");

                    printf(
                        "%-5s | %-12s | %-25s | %-10s | %-15s | %-18s\n",
                        "STT",
                        "Ma PNR",
                        "Ho ten hanh khach",
                        "Hang ve",
                        "Hanh ly (kg)",
                        "Cuoc qua cuoc"
                    );

                    printf("========================================================================================\n");

                    for (int i = 0; i < soLuong; i++) {

                        const char *tenHangVe;

                        if (danhSachVe[i].ticketClass == 1) {
                            tenHangVe = "Eco";
                        } else if (danhSachVe[i].ticketClass == 2) {
                            tenHangVe = "Deluxe";
                        } else {
                            tenHangVe = "Business";
                        }

                        printf(
                            "%-5d | %-12s | %-25s | %-10s | %-15.1f | %-15.0f VND\n",
                            i + 1,
                            danhSachVe[i].pnrCode,
                            danhSachVe[i].passengerName,
                            tenHangVe,
                            danhSachVe[i].baggageWeight,
                            danhSachVe[i].baggageFee
                        );
                    }

                    printf("========================================================================================\n");
                }

                break;
            }

            /* ======================================
               CASE 3: CAP NHAT HANH LY
               ====================================== */

            case 3: {

                if (soLuong == 0) {

                    printf("Danh sach ve dang rong!\n");

                } else {

                    int found = 0;

                    printf("\n--- CAP NHAT HANH LY ---\n");

                    while (getchar() != '\n');

                    printf("Nhap ma PNR can cap nhat hanh ly: ");

                    fgets(
                        pnrInput,
                        sizeof(pnrInput),
                        stdin
                    );

                    pnrInput[
                        strcspn(pnrInput, "\n")
                    ] = '\0';

                    for (int i = 0; i < soLuong; i++) {

                        if (strcmp(
                                danhSachVe[i].pnrCode,
                                pnrInput
                            ) == 0) {

                            found = 1;

                            printf(
                                "Tim thay hanh khach: %s\n",
                                danhSachVe[i].passengerName
                            );

                            printf(
                                "Nhap trong luong hanh ly moi (kg): "
                            );

                            scanf("%f", &baggageWeightInput);

                            while (baggageWeightInput < 0) {

                                printf(
                                    "Khoi luong khong hop le! "
                                    "Vui long nhap lai: "
                                );

                                scanf(
                                    "%f",
                                    &baggageWeightInput
                                );
                            }

                            danhSachVe[i].baggageWeight =
                                baggageWeightInput;

                            /*
                             * Tinh lai phi hanh ly.
                             */

                            if (danhSachVe[i].ticketClass == 3) {

                                danhSachVe[i].baggageFee = 0.0f;

                            } else if (
                                danhSachVe[i].baggageWeight <= 7.0f
                            ) {

                                danhSachVe[i].baggageFee = 0.0f;

                            } else {

                                danhSachVe[i].baggageFee =
                                    (danhSachVe[i].baggageWeight - 7.0f)
                                    * 50000.0f;
                            }

                            printf(
                                "=> Cap nhat thanh cong! "
                                "Phi hanh ly qua cuoc moi: %.0f VND.\n",
                                danhSachVe[i].baggageFee
                            );

                            break;
                        }
                    }

                    if (found == 0) {

                        printf(
                            "Khong tim thay ve co ma PNR da nhap!\n"
                        );
                    }
                }

                break;
            }

            /* ======================================
               CASE 4: XOA VE
               ====================================== */

            case 4: {

                if (soLuong == 0) {

                    printf("Danh sach ve dang rong!\n");

                } else {

                    int found = 0;

                    printf("\n--- XOA VE MAY BAY ---\n");

                    while (getchar() != '\n');

                    printf("Nhap ma PNR can xoa: ");

                    fgets(
                        pnrInput,
                        sizeof(pnrInput),
                        stdin
                    );

                    pnrInput[
                        strcspn(pnrInput, "\n")
                    ] = '\0';

                    for (int i = 0; i < soLuong; i++) {

                        if (strcmp(
                                danhSachVe[i].pnrCode,
                                pnrInput
                            ) == 0) {

                            found = 1;

                            /*
                             * Don cac phan tu phia sau
                             * len mot vi tri.
                             */
                            for (int j = i;
                                 j < soLuong - 1;
                                 j++) {

                                danhSachVe[j] =
                                    danhSachVe[j + 1];
                            }

                            soLuong--;

                            printf(
                                "=> Da xoa thanh cong ve co ma PNR: %s "
                                "ra khoi he thong.\n",
                                pnrInput
                            );

                            break;
                        }
                    }

                    if (found == 0) {

                        printf(
                            "Khong tim thay ve co ma PNR da nhap!\n"
                        );
                    }
                }

                break;
            }

            /* ======================================
               CASE 5: THOAT
               ====================================== */

            case 5:

                printf("\nCam on ban da su dung he thong!\n");
                printf("Tam biet!\n");

                break;

            /* ======================================
               LUA CHON KHONG HOP LE
               ====================================== */

            default:

                printf(
                    "Lua chon khong hop le! "
                    "Vui long chon tu 1 den 5.\n"
                );

                break;
        }

    } while (luaChon != 5);

    return 0;
}