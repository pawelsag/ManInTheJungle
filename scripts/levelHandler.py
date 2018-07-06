import struct
import os
import array

pathToLevel = "C:\SDLPRojects\SDL GAME\config\\" 
pathToLevelProcess = "C:\SDLPRojects\SDL GAME\config\levels\\" 
def decodeLevel(readFileName, writeFileName):
	k=[]

	with open( pathToLevel + readFileName , "rb") as f:
		k =  f.read()
		# read BITMAPFILEHEADRE
		bfType , bfSize, bfRes1, bfRes2, bfOffset = struct.unpack("<HIHHI", k[:14])
		if ( bfType == 'BM' ):
			print("Error, file format incorrect")
			return
		# read BITMAPINFOHEADER
		(
			biSize, biWidth, biHeight, biPLanes, biBitCount, biCompression,  	
			biSizeImage, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrUsed
		) = struct.unpack("<IiiHHIIIIII",k[14 : 14+40])
		print(biWidth ,biHeight)
		
		if( biSize != 40 ):
			print("Incorrect header info size")
			return 
		if( biHeight > 30 or biWidth > 10000):
			print("Map to big ")
			return 
			
		# calc offset for evry row 
		pitch = (biWidth * 3 + 3) & ~3
		NegatiwHeight = False
		#  if height is negative
		if( biHeight < 0 ):
			NegatiwHeight = True
			biHeight = -biHeight
			rGenerator = range(0, biHeight)			
		else:
			rGenerator = range(biHeight-1, -1, -1)

		with open( pathToLevelProcess + writeFileName , "wb") as f2:
			# write x-size
			f2.write( struct.pack( "<I",biWidth ) ) 
			# write y-size
			f2.write( struct.pack( "<I",biHeight ) ) 
			# unpack offset to long int 			
			# read data from bmp file without header
			k = k[ bfOffset: ]
			cleanMap = array.array('B',[0]) * biWidth * biHeight
			# read every third byte, to doceode map, only one pixel is neccessary (RED)
			r = 0
			for row in rGenerator:
				for col in range(biWidth):
					cleanMap[r*biWidth + col] =  k[pitch*row + col*3 +2]  	
				r += 1

			print( cleanMap )
				
			# count all diffrent signs
			countSigns(cleanMap, f2)

			# print(list(k))
			f2.write( bytearray(cleanMap) )

def LoadBmp():

	pass

def countSigns(byteTable, fileDescriptor):
	signs ={}
	counter = 0
	
	for sign in byteTable:
		if(sign in signs):
			signs[sign] +=1
		else:
			signs.update({sign : 1})
			
	
	# offset for data in Bytes
	# dataOffset = sizeof(x_size) + sizeof(y_size) + sizeof(dataOffset_size) + sizeof(signDescription_size)
	dataOffset = struct.pack("<H", (4 + 4 + 2 + len(signs) )  )
	print(dataOffset)
	fileDescriptor.write(dataOffset)
	for key,value in signs.items():
		# print(key)
		fileDescriptor.write(struct.pack("<B", key ) )


def findBmpFiles():
	for file in os.listdir(pathToLevel):
		if(file[-3::] == "bmp" ):
			dstName = file.replace("bmp","bin")
			decodeLevel(file,dstName)		

			

if __name__ == "__main__":
	findBmpFiles()
