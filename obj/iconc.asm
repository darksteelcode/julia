 define .icon,space=ram
 segment .icon
 xdef __icon_begin
 xdef __icon_end
 xdef __program_description
 xdef __program_description_end

 db 1
 db 16,16
__icon_begin:
 db 0FFh,0FFh,0FFh,0F7h,0E5h,0E4h,0F6h,0FFh,0FFh,0F6h,0E4h,0ECh,0FEh,0FFh,0FFh,0FFh
 db 0FFh,0FFh,0F6h,0E4h,0E5h,0EDh,0E5h,0FFh,0FFh,0E4h,0EDh,0E4h,0E4h,0F6h,0FFh,0FFh
 db 0FFh,0FFh,0F6h,0E4h,0EDh,0EDh,0E4h,0FEh,0F6h,0E4h,0EDh,0E5h,0E4h,0F6h,0FFh,0FFh
 db 0FFh,0FFh,0FFh,0EEh,0E4h,0EDh,0E5h,0EDh,0EDh,0E4h,0EDh,0E4h,0F5h,0FFh,0FFh,0FFh
 db 0FFh,0FFh,0FFh,0FFh,0E5h,0E4h,0EDh,0E4h,0E5h,0EDh,0E4h,0EDh,0FFh,0FFh,0FFh,0FFh
 db 0F6h,0F6h,0FFh,0FFh,0FFh,0E4h,0EDh,0EDh,0EDh,0E5h,0E4h,0FFh,0FFh,0FFh,0F6h,0F6h
 db 0E5h,0E4h,0E4h,0E4h,0ECh,0E4h,0E5h,0EDh,0E5h,0E5h,0E4h,0ECh,0E4h,0E3h,0E3h,0ECh
 db 0E5h,0EDh,0EDh,0EDh,0EDh,0ECh,0EDh,0E5h,0E5h,0EDh,0E5h,0E4h,0E5h,0EDh,0E4h,0ECh
 db 0ECh,0E3h,0E3h,0E4h,0ECh,0ECh,0E5h,0E5h,0E5h,0E5h,0E4h,0ECh,0E3h,0E3h,0C3h,0CCh
 db 0FFh,0FFh,0FFh,0FFh,0FFh,0E3h,0EDh,0E5h,0E5h,0E5h,0E4h,0FFh,0FFh,0FFh,0FFh,0FFh
 db 0FFh,0FFh,0FFh,0FFh,0ECh,0E4h,0ECh,0E4h,0E4h,0EDh,0E4h,0ECh,0FFh,0FFh,0FFh,0FFh
 db 0FFh,0FFh,0FFh,0EDh,0E4h,0EDh,0E4h,0F5h,0EDh,0E4h,0E5h,0E3h,0EDh,0FFh,0FFh,0FFh
 db 0FFh,0FFh,0F6h,0E4h,0EDh,0EDh,0E3h,0FFh,0F6h,0E3h,0E5h,0E4h,0C3h,0F6h,0FFh,0FFh
 db 0FFh,0FFh,0F6h,0E3h,0E4h,0E4h,0EDh,0FFh,0FFh,0E3h,0E4h,0E3h,0C3h,0F5h,0FFh,0FFh
 db 0FFh,0FFh,0FFh,0FEh,0ECh,0ECh,0FEh,0FFh,0FFh,0F5h,0CBh,0EDh,0FFh,0FFh,0FFh,0FFh
 db 0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh
__icon_end:
__program_description:
 db "JULIA",0
__program_description_end:
