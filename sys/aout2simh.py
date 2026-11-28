import struct

out = open("load.cmd", "w")
mmr0 = 0o177572
mmr1 = 0o177574
mmr2 = 0o177576
mmr3 = 0o177516
uisdb = 0o177600
udsdb = 0o177620
uisab = 0o177640
udsab = 0o177660

with open('vmunix', 'rb') as file:
    magic = 0
    text_size = 0
    data_size = 0
    bss_size = 0
    text_base = 0
    data_base = 0
    stack_base = 0

    magic = int.from_bytes(file.read(2), byteorder="little", signed=False)
    text_size = int.from_bytes(file.read(2), byteorder="little", signed=False)
    data_size = int.from_bytes(file.read(2), byteorder="little", signed=False)
    bss_size = int.from_bytes(file.read(2), byteorder="little", signed=False)

    file.seek(16, 0)
    text_array = bytearray(file.read(text_size))
    data_array = bytearray(file.read(data_size))
    data_base = (text_size + 63) & ~63
    stack_base = (((data_base + data_size + bss_size) + 8191) & ~8191)

    print(f"magic={magic:06o} text_size={text_size:06o} data_size={data_size:06o} bss_size={bss_size:06o} text_base={text_base:06o} data_base={data_base:06o} stack_base={stack_base:08o}")

    out.write("set cpu history=1000\n")
    out.write("set cpu 2M\n")
        

    if text_size & 1:
        text_array.append(0)
    if data_size & 1:
        data_array.append(0)

    # map .text
    for i in range(0, len(text_array), 2):
        #chunk = int.from_bytes(text_array[i:i+1])
        chunk = struct.unpack('<H', text_array[i:i+2])[0]
        out.write(f"d {i+text_base:06o} {chunk:06o}\n")

    # map .data
    for i in range(0, len(data_array), 2):
        chunk = struct.unpack('<H', data_array[i:i+2])[0]
        out.write(f"d {i+data_base:06o} {chunk:06o}\n")

    
    # program user-space CSRs
    # map .text into memory
    if (text_size // 8192) == 0:
        out.write(f"d KIPDR0 {(6 | (((text_size // 64) | 1) << 8)):06o}\n")
        out.write(f"d KIPAR0 {(text_base >> 6):06o}\n")
    else:
        for i in range(0, text_size // 8192, 1):
            out.write(f"d KIPDR{i} 077406\n")
            out.write(f"d KIPAR{i} {((text_base + (i * 8192)) >> 6):06o}\n")

    # map .data into memory
    if ((data_size + bss_size) // 8192) == 0:
            out.write(f"d KDPDR0 {(6 | (((data_size // 64) | 1) << 8)):06o}\n")
            out.write(f"d KDPAR0 {(data_base >> 6):06o}\n")
    else:
        for i in range(0, (data_size + bss_size) // 8192, 1):
            out.write(f"d KDPDR{i} 077406\n")
            out.write(f"d KDPAR{i} {((data_base + (i * 8192)) >> 6):06o}\n")

    out.write(f"d KDPDR7 077406\n")
    out.write(f"d KDPAR7 177600\n")
    out.write(f"d KDPDR6 077406\n")
    out.write(f"d KDPAR6 {stack_base >> 6:06o}\n")
    out.write("d psw 000340\n")
    out.write("d sp 160000\n")
    out.write("d ksp 160000\n")
    out.write("d mmr0 000001\n")
    out.write("d mmr3 000024\n")
    