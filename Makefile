MCU  = stm8s003f3
ARCH = stm8

TARGET  ?= bin/client.ihx

LIBRARY_SRCS := $(wildcard lib/*.c)

OBJS   = $(patsubst %, bin/%, $(LIBRARY_SRCS:.c=.rel)) bin/src/main.rel

CC       = sdcc
LD       = sdld
AS       = sdasstm8

ASFLAGS  = -plosgff

CFLAGS   = -m$(ARCH) -p$(MCU) --std-sdcc11
CFLAGS  += -I. -Ilib
CFLAGS  += --stack-auto --noinduction --use-non-free

LDFLAGS     = -m$(ARCH) -l$(ARCH) --out-fmt-ihx
BIN_LDFLAGS = -m$(ARCH) -l$(ARCH) --out-fmt-bin

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	sdobjcopy -I ihex --output-target=binary $(TARGET) $(TARGET).bin
	@echo "Image size: \c"
	@stat -f%z $(TARGET).bin

bin/%.rel: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

flash: $(TARGET)
	stm8flash -c stlinkv2 -p $(MCU) -w $(TARGET)

clean:
	rm -r bin

.PHONY: clean all flash