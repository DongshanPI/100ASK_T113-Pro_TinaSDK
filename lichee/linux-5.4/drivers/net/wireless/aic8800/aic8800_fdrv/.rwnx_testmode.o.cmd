cmd_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.o := /home/yuzuki/WorkSpcae/tina-a133-5.0/out/toolchain/gcc-linaro-5.3.1-2016.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc -Wp,-MD,drivers/net/wireless/aic8800/aic8800_fdrv/.rwnx_testmode.o.d  -nostdinc -isystem /home/yuzuki/WorkSpcae/tina-a133-5.0/out/toolchain/gcc-linaro-5.3.1-2016.05-x86_64_aarch64-linux-gnu/bin/../lib/gcc/aarch64-linux-gnu/5.3.1/include -I./arch/arm64/include -I./arch/arm64/include/generated/uapi -I./arch/arm64/include/generated  -I./include -I./arch/arm64/include/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -fno-PIE -mgeneral-regs-only -DCONFIG_AS_LSE=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -fno-pic -fno-delete-null-pointer-checks -Os -Wno-maybe-uninitialized --param=allow-store-data-races=0 -DCC_HAVE_ASM_GOTO -Wframe-larger-than=2048 -fstack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-merge-all-constants -fmerge-constants -fno-stack-check -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -Werror=incompatible-pointer-types -DCONFIG_RWNX_DEBUGFS -DCONFIG_RWNX_UM_HELPER_DFLT=\""/dini/dini_bin/rwnx_umh.sh"\" -DNX_VIRT_DEV_MAX=4 -DNX_REMOTE_STA_MAX_FOR_OLD_IC=10 -DNX_REMOTE_STA_MAX=32 -DNX_MU_GROUP_MAX=62 -DNX_TXDESC_CNT=64 -DNX_TX_MAX_RATES=4 -DNX_CHAN_CTXT_CNT=3 -DCONFIG_START_FROM_BOOTROM -DCONFIG_PMIC_SETTING -DCONFIG_VRF_DCDC_MODE -DCONFIG_ROM_PATCH_EN -DCONFIG_COEX -DCONFIG_RWNX_FULLMAC -I. -I./drivers/net/wireless/aic8800/aic8800_fdrv -I./drivers/net/wireless/aic8800/aic8800_fdrv/../aic8800_bsp -DCONFIG_AIC_FW_PATH=\""/vendor/etc/firmware"\" -DCONFIG_RWNX_RADAR -DCONFIG_RWNX_MON_DATA -DCONFIG_RWNX_DBG -DCONFIG_RFTEST -DDEFAULT_COUNTRY_CODE=""\"00""\" -DCONFIG_SUPPORT_REALTIME_CHANGE_MAC -DCONFIG_SCHED_SCAN -DCONFIG_PREALLOC_TXQ -DAICWF_SDIO_SUPPORT -DCONFIG_SDIO_PWRCTRL -DCONFIG_USER_MAX=1 -DNX_TXQ_CNT=5 -DAICWF_RX_REORDER -DAICWF_ARP_OFFLOAD -DCONFIG_RX_NETIF_RECV_SKB -DAIC_TRACE_INCLUDE_PATH=drivers/net/wireless/aic8800/aic8800_fdrv -DCONFIG_PLATFORM_ALLWINNER -DANDROID_PLATFORM  -DMODULE -mcmodel=large  -DKBUILD_BASENAME='"rwnx_testmode"'  -DKBUILD_MODNAME='"aic8800_fdrv"' -c -o drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.o drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.c

source_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.o := drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.c

deps_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.o := \
  include/net/mac80211.h \
    $(wildcard include/config/mac80211/debugfs.h) \
    $(wildcard include/config/mac80211/mesh.h) \
    $(wildcard include/config/type/restart.h) \
    $(wildcard include/config/type/suspend.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/nl80211/testmode.h) \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/mac80211/leds.h) \
  include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/bug/on/data/corruption.h) \
  arch/arm64/include/asm/bug.h \
    $(wildcard include/config/debug/bugverbose.h) \
  arch/arm64/include/asm/brk-imm.h \
  include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/smp.h) \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/kasan.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/gcov/kernel.h) \
    $(wildcard include/config/stack/validation.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  include/uapi/linux/types.h \
  arch/arm64/include/generated/asm/types.h \
  include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/arm64/include/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
    $(wildcard include/config/64bit.h) \
  include/uapi/asm-generic/bitsperlong.h \
  include/uapi/linux/posix_types.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  arch/arm64/include/uapi/asm/posix_types.h \
  include/uapi/asm-generic/posix_types.h \
  include/linux/kasan-checks.h \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/yuzuki/WorkSpcae/tina-a133-5.0/out/toolchain/gcc-linaro-5.3.1-2016.05-x86_64_aarch64-linux-gnu/lib/gcc/aarch64-linux-gnu/5.3.1/include/stdarg.h \
  include/linux/linkage.h \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/trim/unused/ksyms.h) \
    $(wildcard include/config/unused/symbols.h) \
  arch/arm64/include/asm/linkage.h \
  include/linux/types.h \
    $(wildcard include/config/have/uid16.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
  include/linux/bitops.h \
  include/linux/bits.h \
  arch/arm64/include/asm/bitops.h \
  arch/arm64/include/asm/barrier.h \
  include/asm-generic/barrier.h \
  include/asm-generic/bitops/builtin-__ffs.h \
  include/asm-generic/bitops/builtin-ffs.h \
  include/asm-generic/bitops/builtin-__fls.h \
  include/asm-generic/bitops/builtin-fls.h \
  include/asm-generic/bitops/ffz.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/le.h \
  arch/arm64/include/uapi/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/uapi/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  include/uapi/linux/swab.h \
  arch/arm64/include/generated/asm/swab.h \
  include/uapi/asm-generic/swab.h \
  include/linux/byteorder/generic.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/typecheck.h \
  include/linux/printk.h \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk/nmi.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/debug/rodata.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
    $(wildcard include/config/lto/clang.h) \
  include/linux/kern_levels.h \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  include/uapi/linux/kernel.h \
  include/uapi/linux/sysinfo.h \
  arch/arm64/include/asm/cache.h \
  arch/arm64/include/asm/cachetype.h \
  arch/arm64/include/asm/cputype.h \
  arch/arm64/include/asm/sysreg.h \
    $(wildcard include/config/arm64/4k/pages.h) \
    $(wildcard include/config/arm64/16k/pages.h) \
    $(wildcard include/config/arm64/64k/pages.h) \
  arch/arm64/include/asm/opcodes.h \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/cpu/endian/be8.h) \
  arch/arm64/include/../../arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be32.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/if_ether.h \
  include/linux/skbuff.h \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/xfrm.h) \
    $(wildcard include/config/ipv6/ndisc/nodetype.h) \
    $(wildcard include/config/net/switchdev.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/net/rx/busy/poll.h) \
    $(wildcard include/config/xps.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/network/phy/timestamping.h) \
    $(wildcard include/config/netfilter/xt/target/trace.h) \
    $(wildcard include/config/nf/tables.h) \
    $(wildcard include/config/ip/vs.h) \
  include/linux/kmemcheck.h \
    $(wildcard include/config/kmemcheck.h) \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/userfaultfd.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/pgtable/levels.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/arch/want/batched/unmap/tlb/flush.h) \
    $(wildcard include/config/x86/intel/mpx.h) \
    $(wildcard include/config/hugetlb/page.h) \
  include/linux/auxvec.h \
  include/uapi/linux/auxvec.h \
  arch/arm64/include/uapi/asm/auxvec.h \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
    $(wildcard include/config/page/poisoning/zero.h) \
  include/uapi/linux/const.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  arch/arm64/include/generated/asm/preempt.h \
  include/asm-generic/preempt.h \
  include/linux/thread_info.h \
    $(wildcard include/config/thread/info/in/task.h) \
    $(wildcard include/config/have/arch/within/stack/frames.h) \
    $(wildcard include/config/hardened/usercopy.h) \
  include/linux/restart_block.h \
    $(wildcard include/config/compat.h) \
  arch/arm64/include/asm/current.h \
  arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/arm64/sw/ttbr0/pan.h) \
  arch/arm64/include/asm/stack_pointer.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  arch/arm64/include/asm/irqflags.h \
  arch/arm64/include/asm/ptrace.h \
  arch/arm64/include/uapi/asm/ptrace.h \
  arch/arm64/include/asm/hwcap.h \
  arch/arm64/include/uapi/asm/hwcap.h \
  include/asm-generic/ptrace.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  arch/arm64/include/asm/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
  include/linux/rwlock_types.h \
  arch/arm64/include/asm/spinlock.h \
  arch/arm64/include/asm/lse.h \
    $(wildcard include/config/as/lse.h) \
    $(wildcard include/config/arm64/lse/atomics.h) \
  arch/arm64/include/asm/processor.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/uapi/linux/string.h \
  arch/arm64/include/asm/string.h \
  arch/arm64/include/asm/alternative.h \
    $(wildcard include/config/arm64/uao.h) \
    $(wildcard include/config/foo.h) \
  arch/arm64/include/asm/cpucaps.h \
  arch/arm64/include/asm/insn.h \
  arch/arm64/include/asm/fpsimd.h \
  arch/arm64/include/asm/hw_breakpoint.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
  arch/arm64/include/asm/cpufeature.h \
    $(wildcard include/config/arm64/ssbd.h) \
  include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  arch/arm64/include/asm/jump_label.h \
  arch/arm64/include/asm/virt.h \
    $(wildcard include/config/arm64/vhe.h) \
  arch/arm64/include/asm/sections.h \
  include/asm-generic/sections.h \
  arch/arm64/include/asm/pgtable-hwdef.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  include/linux/atomic.h \
    $(wildcard include/config/generic/atomic64.h) \
  arch/arm64/include/asm/atomic.h \
  arch/arm64/include/asm/atomic_ll_sc.h \
  arch/arm64/include/asm/cmpxchg.h \
  include/asm-generic/atomic-long.h \
  include/linux/rbtree.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/rcu/stall/common.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/tasks/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/rcu/nocb/cpu/all.h) \
    $(wildcard include/config/no/hz/full/sysidle.h) \
  include/linux/cpumask.h \
    $(wildcard include/config/debug/per/cpu/maps.h) \
  include/linux/bitmap.h \
    $(wildcard include/config/s390.h) \
  include/linux/seqlock.h \
  include/linux/completion.h \
  include/linux/wait.h \
  include/uapi/linux/wait.h \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/ktime.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  arch/arm64/include/generated/asm/div64.h \
  include/asm-generic/div64.h \
  include/linux/time64.h \
  include/uapi/linux/time.h \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/uapi/linux/timex.h \
  include/uapi/linux/param.h \
  arch/arm64/include/uapi/asm/param.h \
  include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  include/uapi/asm-generic/param.h \
  arch/arm64/include/asm/timex.h \
  arch/arm64/include/asm/arch_timer.h \
    $(wildcard include/config/fsl/erratum/a008585.h) \
    $(wildcard include/config/arch/sun50iw1p1.h) \
    $(wildcard include/config/arch/sun50iw2p1.h) \
    $(wildcard include/config/clocksource/validate/last/cycle.h) \
  include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/arm/arch/timer.h) \
  include/linux/timecounter.h \
  include/asm-generic/timex.h \
  include/generated/timeconst.h \
  include/linux/timekeeping.h \
  include/linux/errno.h \
  include/uapi/linux/errno.h \
  arch/arm64/include/generated/asm/errno.h \
  include/uapi/asm-generic/errno.h \
  include/uapi/asm-generic/errno-base.h \
  include/linux/rcutree.h \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/err.h \
  include/linux/osq_lock.h \
  arch/arm64/include/generated/asm/rwsem.h \
  include/asm-generic/rwsem.h \
  include/linux/uprobes.h \
    $(wildcard include/config/uprobes.h) \
  include/linux/page-flags-layout.h \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/generated/bounds.h \
  arch/arm64/include/asm/sparsemem.h \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/wq/watchdog.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
    $(wildcard include/config/no/hz/common.h) \
  include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/uidgid.h \
    $(wildcard include/config/multiuser.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/highuid.h \
  include/uapi/linux/sysctl.h \
  arch/arm64/include/asm/page.h \
    $(wildcard include/config/arm64/page/shift.h) \
    $(wildcard include/config/arm64/cont/shift.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  include/linux/personality.h \
  include/uapi/linux/personality.h \
  arch/arm64/include/asm/pgtable-types.h \
  include/asm-generic/pgtable-nopud.h \
  arch/arm64/include/asm/memory.h \
    $(wildcard include/config/arm64/va/bits.h) \
    $(wildcard include/config/blk/dev/initrd.h) \
  arch/arm64/include/generated/asm/sizes.h \
  include/asm-generic/sizes.h \
  include/linux/sizes.h \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
    $(wildcard include/config/debug/vm/pgflags.h) \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
  include/linux/pfn.h \
  include/asm-generic/getorder.h \
  arch/arm64/include/asm/mmu.h \
    $(wildcard include/config/unmap/kernel/at/el0.h) \
    $(wildcard include/config/harden/branch/predictor.h) \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/smp.h \
    $(wildcard include/config/up/late/init.h) \
  include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  arch/arm64/include/asm/smp.h \
    $(wildcard include/config/arm64/acpi/parking/protocol.h) \
  arch/arm64/include/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/percpu-defs.h \
    $(wildcard include/config/page/table/isolation.h) \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  include/linux/socket.h \
    $(wildcard include/config/proc/fs.h) \
  arch/arm64/include/generated/asm/socket.h \
  include/uapi/asm-generic/socket.h \
  arch/arm64/include/generated/asm/sockios.h \
  include/uapi/asm-generic/sockios.h \
  include/uapi/linux/sockios.h \
  include/linux/uio.h \
  include/uapi/linux/uio.h \
  include/uapi/linux/socket.h \
  include/linux/net.h \
  include/linux/random.h \
    $(wildcard include/config/gcc/plugin/latent/entropy.h) \
    $(wildcard include/config/arch/random.h) \
  include/linux/once.h \
  include/uapi/linux/random.h \
  include/uapi/linux/ioctl.h \
  arch/arm64/include/generated/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/uapi/asm-generic/ioctl.h \
  include/linux/irqnr.h \
  include/uapi/linux/irqnr.h \
  include/linux/fcntl.h \
  include/uapi/linux/fcntl.h \
  arch/arm64/include/uapi/asm/fcntl.h \
  include/uapi/asm-generic/fcntl.h \
  include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/cgroup/writeback.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/fs/encryption.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fs/dax.h) \
    $(wildcard include/config/mandatory/file/locking.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/migration.h) \
  include/linux/kdev_t.h \
  include/uapi/linux/kdev_t.h \
  include/linux/dcache.h \
  include/linux/rculist.h \
  include/linux/rculist_bl.h \
  include/linux/list_bl.h \
  include/linux/bit_spinlock.h \
  include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  include/linux/stringhash.h \
    $(wildcard include/config/dcache/word/access.h) \
  include/linux/hash.h \
    $(wildcard include/config/have/arch/hash.h) \
  include/linux/path.h \
  include/linux/stat.h \
  arch/arm64/include/asm/stat.h \
  arch/arm64/include/uapi/asm/stat.h \
  include/uapi/asm-generic/stat.h \
  arch/arm64/include/asm/compat.h \
  include/linux/sched.h \
    $(wildcard include/config/cpu/quiet.h) \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/bpf/syscall.h) \
    $(wildcard include/config/sched/info.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/walt.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/psi.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/cpu/freq/times.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/ubsan.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/kcov.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/vmap/stack.h) \
    $(wildcard include/config/arch/wants/dynamic/task/struct.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/have/copy/thread/tls.h) \
    $(wildcard include/config/have/exit/thread.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/cpu/freq.h) \
  include/uapi/linux/sched.h \
  include/linux/sched/prio.h \
  include/linux/capability.h \
  include/uapi/linux/capability.h \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/nodemask.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/movable/node.h) \
  include/linux/cputime.h \
  arch/arm64/include/generated/asm/cputime.h \
  include/asm-generic/cputime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  include/asm-generic/cputime_jiffies.h \
  include/linux/sem.h \
  include/uapi/linux/sem.h \
  include/linux/ipc.h \
  include/uapi/linux/ipc.h \
  arch/arm64/include/generated/asm/ipcbuf.h \
  include/uapi/asm-generic/ipcbuf.h \
  arch/arm64/include/generated/asm/sembuf.h \
  include/uapi/asm-generic/sembuf.h \
  include/linux/shm.h \
  include/uapi/linux/shm.h \
  arch/arm64/include/generated/asm/shmbuf.h \
  include/uapi/asm-generic/shmbuf.h \
  arch/arm64/include/asm/shmparam.h \
  include/uapi/asm-generic/shmparam.h \
  include/linux/signal.h \
    $(wildcard include/config/old/sigaction.h) \
  include/uapi/linux/signal.h \
  arch/arm64/include/uapi/asm/signal.h \
  include/asm-generic/signal.h \
  include/uapi/asm-generic/signal.h \
  include/uapi/asm-generic/signal-defs.h \
  arch/arm64/include/uapi/asm/sigcontext.h \
  arch/arm64/include/uapi/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/uapi/asm-generic/siginfo.h \
  include/linux/pid.h \
  include/linux/topology.h \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zsmalloc.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/zone/device.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/page/extension.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/deferred/struct/page/init.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  include/linux/notifier.h \
  include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  include/linux/mutex-debug.h \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  include/linux/srcu.h \
  arch/arm64/include/asm/topology.h \
  include/asm-generic/topology.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/have/arch/seccomp/filter.h) \
    $(wildcard include/config/seccomp/filter.h) \
    $(wildcard include/config/checkpoint/restore.h) \
  include/uapi/linux/seccomp.h \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/resource.h \
  include/uapi/linux/resource.h \
  arch/arm64/include/generated/asm/resource.h \
  include/asm-generic/resource.h \
  include/uapi/asm-generic/resource.h \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/time/low/res.h) \
    $(wildcard include/config/timerfd.h) \
  include/linux/timerqueue.h \
  include/linux/kcov.h \
  include/uapi/linux/kcov.h \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
  include/linux/key.h \
  include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/gfp.h \
    $(wildcard include/config/pm/sleep.h) \
  include/uapi/linux/magic.h \
  include/uapi/linux/stat.h \
  include/linux/list_lru.h \
  include/linux/shrinker.h \
  include/linux/radix-tree.h \
    $(wildcard include/config/radix/tree/multiorder.h) \
  include/linux/semaphore.h \
  include/uapi/linux/fiemap.h \
  include/linux/migrate_mode.h \
  include/linux/percpu-rwsem.h \
  include/linux/rcu_sync.h \
  include/linux/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  include/linux/bvec.h \
  include/linux/delayed_call.h \
  include/uapi/linux/fs.h \
  include/uapi/linux/limits.h \
  include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  include/linux/percpu_counter.h \
  include/uapi/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/projid.h \
  include/uapi/linux/quota.h \
  include/linux/nfs_fs_i.h \
  include/uapi/linux/net.h \
  include/linux/textsearch.h \
  include/linux/slab.h \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/have/hardened/usercopy/allocator.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
  include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  include/linux/kasan.h \
  include/net/checksum.h \
  arch/arm64/include/asm/uaccess.h \
    $(wildcard include/config/arm64/pan.h) \
  arch/arm64/include/asm/kernel-pgtable.h \
  arch/arm64/include/asm/pgtable.h \
    $(wildcard include/config/arm64/hw/afdbm.h) \
  arch/arm64/include/asm/proc-fns.h \
  arch/arm64/include/asm/pgtable-prot.h \
  arch/arm64/include/asm/fixmap.h \
  arch/arm64/include/asm/boot.h \
  include/asm-generic/fixmap.h \
  include/asm-generic/pgtable.h \
    $(wildcard include/config/have/arch/soft/dirty.h) \
    $(wildcard include/config/have/arch/huge/vmap.h) \
  arch/arm64/include/asm/compiler.h \
  arch/arm64/include/asm/checksum.h \
  include/asm-generic/checksum.h \
  include/linux/dma-mapping.h \
    $(wildcard include/config/have/generic/dma/coherent.h) \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/arch/has/dma/set/coherent/mask.h) \
    $(wildcard include/config/need/dma/map/state.h) \
    $(wildcard include/config/dma/api/debug.h) \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/generic/msi/irq/domain.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/generic/msi/irq.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  include/linux/ioport.h \
  include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  include/linux/sysfs.h \
  include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  include/linux/idr.h \
  include/linux/kobject_ns.h \
  include/linux/kref.h \
  include/linux/refcount.h \
    $(wildcard include/config/refcount/full.h) \
    $(wildcard include/config/arch/has/refcount.h) \
  include/linux/klist.h \
  include/linux/pinctrl/devinfo.h \
  include/linux/pinctrl/consumer.h \
    $(wildcard include/config/pinconf.h) \
  include/linux/seq_file.h \
  include/linux/pinctrl/pinctrl-state.h \
  include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  include/linux/ratelimit.h \
  arch/arm64/include/asm/device.h \
    $(wildcard include/config/iommu/api.h) \
  include/linux/pm_wakeup.h \
  include/linux/dma-debug.h \
  include/linux/dma-direction.h \
  include/linux/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
    $(wildcard include/config/need/sg/dma/length.h) \
    $(wildcard include/config/arch/has/sg/chain.h) \
    $(wildcard include/config/sg/pool.h) \
  include/linux/mm.h \
    $(wildcard include/config/have/arch/mmap/rnd/bits.h) \
    $(wildcard include/config/have/arch/mmap/rnd/compat/bits.h) \
    $(wildcard include/config/mem/soft/dirty.h) \
    $(wildcard include/config/arch/uses/high/vma/flags.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/x86/intel/memory/protection/keys.h) \
    $(wildcard include/config/ppc.h) \
    $(wildcard include/config/parisc.h) \
    $(wildcard include/config/metag.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/shmem.h) \
    $(wildcard include/config/debug/vm/rb.h) \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/hugetlbfs.h) \
  include/linux/range.h \
  include/linux/percpu-refcount.h \
  include/linux/page_ext.h \
    $(wildcard include/config/idle/page/tracking.h) \
  include/linux/stacktrace.h \
    $(wildcard include/config/stacktrace.h) \
    $(wildcard include/config/user/stacktrace/support.h) \
  include/linux/stackdepot.h \
  include/linux/page_ref.h \
    $(wildcard include/config/debug/page/ref.h) \
  include/linux/page-flags.h \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/ksm.h) \
  include/linux/tracepoint-defs.h \
  include/linux/static_key.h \
  include/linux/huge_mm.h \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
    $(wildcard include/config/debug/tlbflush.h) \
    $(wildcard include/config/debug/vm/vmacache.h) \
  include/linux/vm_event_item.h \
    $(wildcard include/config/memory/balloon.h) \
    $(wildcard include/config/balloon/compaction.h) \
  arch/arm64/include/asm/io.h \
  arch/arm64/include/generated/asm/early_ioremap.h \
  include/asm-generic/early_ioremap.h \
    $(wildcard include/config/generic/early/ioremap.h) \
  include/xen/xen.h \
    $(wildcard include/config/xen.h) \
    $(wildcard include/config/xen/dom0.h) \
    $(wildcard include/config/xen/pvh.h) \
  include/asm-generic/io.h \
    $(wildcard include/config/generic/iomap.h) \
    $(wildcard include/config/has/ioport/map.h) \
    $(wildcard include/config/virt/to/bus.h) \
  include/asm-generic/pci_iomap.h \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  include/linux/vmalloc.h \
  arch/arm64/include/asm/dma-mapping.h \
    $(wildcard include/config/iommu/dma.h) \
  arch/arm64/include/asm/xen/hypervisor.h \
  arch/arm64/include/../../arm/include/asm/xen/hypervisor.h \
  include/linux/netdev_features.h \
  include/net/flow_dissector.h \
  include/linux/in6.h \
  include/uapi/linux/in6.h \
  include/uapi/linux/libc-compat.h \
    $(wildcard include/config/data.h) \
  include/linux/siphash.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  include/uapi/linux/if_ether.h \
  include/linux/splice.h \
  include/linux/pipe_fs_i.h \
  include/uapi/linux/if_packet.h \
  include/net/flow.h \
  include/linux/ieee80211.h \
    $(wildcard include/config/timeout.h) \
  include/linux/etherdevice.h \
  include/linux/netdevice.h \
    $(wildcard include/config/dcb.h) \
    $(wildcard include/config/net/ethtool.h) \
    $(wildcard include/config/hyperv/net.h) \
    $(wildcard include/config/wlan.h) \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/rps.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/bql.h) \
    $(wildcard include/config/rfs/accel.h) \
    $(wildcard include/config/fcoe.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/libfcoe.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/net/l3/master/dev.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/tipc.h) \
    $(wildcard include/config/mpls/routing.h) \
    $(wildcard include/config/netfilter/ingress.h) \
    $(wildcard include/config/cgroup/net/prio.h) \
    $(wildcard include/config/net/flow/limit.h) \
  include/linux/delay.h \
  arch/arm64/include/generated/asm/delay.h \
  include/asm-generic/delay.h \
  include/linux/prefetch.h \
  include/linux/dmaengine.h \
    $(wildcard include/config/async/tx/enable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/rapidio/dma/engine.h) \
    $(wildcard include/config/async/tx/dma.h) \
  include/linux/dynamic_queue_limits.h \
  include/linux/ethtool.h \
  include/linux/compat.h \
    $(wildcard include/config/compat/old/sigaction.h) \
    $(wildcard include/config/odd/rt/sigaction.h) \
  include/uapi/linux/if.h \
  include/uapi/linux/hdlc/ioctl.h \
  include/uapi/linux/aio_abi.h \
  include/uapi/linux/unistd.h \
  arch/arm64/include/asm/unistd.h \
  arch/arm64/include/uapi/asm/unistd.h \
  include/asm-generic/unistd.h \
  include/uapi/asm-generic/unistd.h \
  include/uapi/linux/ethtool.h \
  include/net/net_namespace.h \
    $(wildcard include/config/ieee802154/6lowpan.h) \
    $(wildcard include/config/ip/sctp.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/nf/defrag/ipv6.h) \
    $(wildcard include/config/netfilter/netlink/acct.h) \
    $(wildcard include/config/nf/ct/netlink/timeout.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/mpls.h) \
    $(wildcard include/config/net/ns.h) \
  include/net/netns/core.h \
  include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
  include/net/snmp.h \
  include/uapi/linux/snmp.h \
  include/linux/u64_stats_sync.h \
  include/net/netns/unix.h \
  include/net/netns/packet.h \
  include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/route/classid.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
    $(wildcard include/config/ip/route/multipath.h) \
  include/net/inet_frag.h \
  include/linux/rhashtable.h \
  include/linux/jhash.h \
  include/linux/unaligned/packed_struct.h \
  include/linux/list_nulls.h \
  include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  include/net/dst_ops.h \
  include/net/netns/ieee802154_6lowpan.h \
  include/net/netns/sctp.h \
  include/net/netns/dccp.h \
  include/net/netns/netfilter.h \
  include/linux/netfilter_defs.h \
  include/uapi/linux/netfilter.h \
  include/linux/in.h \
  include/uapi/linux/in.h \
  include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
  include/net/netns/conntrack.h \
    $(wildcard include/config/nf/conntrack/events.h) \
    $(wildcard include/config/nf/conntrack/labels.h) \
  include/linux/netfilter/nf_conntrack_tcp.h \
  include/uapi/linux/netfilter/nf_conntrack_tcp.h \
  include/net/netns/nftables.h \
  include/net/netns/xfrm.h \
  include/uapi/linux/xfrm.h \
  include/net/flowcache.h \
  include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  include/linux/irqreturn.h \
  include/linux/hardirq.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
    $(wildcard include/config/hwlat/tracer.h) \
  include/linux/vtime.h \
  include/linux/context_tracking_state.h \
    $(wildcard include/config/context/tracking.h) \
  arch/arm64/include/asm/hardirq.h \
  arch/arm64/include/asm/irq.h \
  include/asm-generic/irq.h \
  include/linux/irq_cpustat.h \
  include/net/netns/mpls.h \
  include/linux/ns_common.h \
  include/linux/seq_file_net.h \
  include/linux/nsproxy.h \
  include/net/dsa.h \
    $(wildcard include/config/net/dsa/hwmon.h) \
  include/linux/of.h \
    $(wildcard include/config/sparc.h) \
    $(wildcard include/config/of/dynamic.h) \
    $(wildcard include/config/attach/node.h) \
    $(wildcard include/config/detach/node.h) \
    $(wildcard include/config/add/property.h) \
    $(wildcard include/config/remove/property.h) \
    $(wildcard include/config/update/property.h) \
    $(wildcard include/config/of/numa.h) \
    $(wildcard include/config/no/change.h) \
    $(wildcard include/config/change/add.h) \
    $(wildcard include/config/change/remove.h) \
    $(wildcard include/config/of/resolve.h) \
    $(wildcard include/config/of/overlay.h) \
  include/linux/mod_devicetable.h \
  include/linux/uuid.h \
  include/uapi/linux/uuid.h \
  include/linux/property.h \
  include/linux/fwnode.h \
  include/linux/phy.h \
  include/linux/mdio.h \
  include/uapi/linux/mdio.h \
  include/linux/mii.h \
  include/uapi/linux/mii.h \
  include/linux/module.h \
    $(wildcard include/config/param/sysfs.h) \
    $(wildcard include/config/modules/tree/lookup.h) \
    $(wildcard include/config/livepatch.h) \
    $(wildcard include/config/cfi/clang.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
  include/linux/kmod.h \
  include/linux/elf.h \
  arch/arm64/include/asm/elf.h \
  arch/arm64/include/generated/asm/user.h \
  include/asm-generic/user.h \
  include/uapi/linux/elf.h \
  include/uapi/linux/elf-em.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ppc64.h) \
  include/linux/extable.h \
  include/linux/rbtree_latch.h \
  include/linux/cfi.h \
    $(wildcard include/config/cfi/clang/shadow.h) \
  arch/arm64/include/asm/module.h \
    $(wildcard include/config/arm64/module/plts.h) \
    $(wildcard include/config/randomize/base.h) \
  include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  include/linux/phy_fixed.h \
    $(wildcard include/config/fixed/phy.h) \
  include/net/netprio_cgroup.h \
  include/linux/cgroup.h \
    $(wildcard include/config/sock/cgroup/data.h) \
    $(wildcard include/config/cgroup/net/classid.h) \
    $(wildcard include/config/cgroup/data.h) \
  include/uapi/linux/cgroupstats.h \
  include/uapi/linux/taskstats.h \
  include/linux/user_namespace.h \
    $(wildcard include/config/persistent/keyrings.h) \
  include/linux/cgroup-defs.h \
  include/linux/bpf-cgroup.h \
    $(wildcard include/config/cgroup/bpf.h) \
  include/uapi/linux/bpf.h \
  include/uapi/linux/bpf_common.h \
  include/linux/psi_types.h \
  include/linux/kthread.h \
  include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/schedtune.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/cgroup/hugetlb.h) \
    $(wildcard include/config/cgroup/pids.h) \
    $(wildcard include/config/cgroup/debug.h) \
  include/uapi/linux/neighbour.h \
  include/linux/netlink.h \
  include/net/scm.h \
    $(wildcard include/config/security/network.h) \
  include/linux/security.h \
    $(wildcard include/config/security/network/xfrm.h) \
    $(wildcard include/config/security/path.h) \
    $(wildcard include/config/securityfs.h) \
  include/uapi/linux/netlink.h \
  include/uapi/linux/netdevice.h \
  include/linux/if_link.h \
  include/uapi/linux/if_link.h \
    $(wildcard include/config/pending.h) \
  include/uapi/linux/if_bonding.h \
  include/uapi/linux/pkt_cls.h \
    $(wildcard include/config/net/cls/ind.h) \
  include/uapi/linux/pkt_sched.h \
  include/linux/hashtable.h \
  arch/arm64/include/generated/asm/unaligned.h \
  include/asm-generic/unaligned.h \
  include/linux/unaligned/access_ok.h \
  include/linux/unaligned/generic.h \
  include/net/cfg80211.h \
    $(wildcard include/config/cfg80211.h) \
    $(wildcard include/config/cfg80211/wext.h) \
  include/linux/debugfs.h \
    $(wildcard include/config/debug/fs.h) \
  include/uapi/linux/nl80211.h \
  include/net/regulatory.h \
  include/net/codel.h \
  include/net/pkt_sched.h \
  include/linux/if_vlan.h \
  include/linux/rtnetlink.h \
    $(wildcard include/config/net/ingress.h) \
    $(wildcard include/config/net/egress.h) \
  include/uapi/linux/rtnetlink.h \
  include/uapi/linux/if_addr.h \
  include/uapi/linux/if_vlan.h \
  include/net/sch_generic.h \
  include/uapi/linux/pkt_cls.h \
  include/net/gen_stats.h \
  include/uapi/linux/gen_stats.h \
  include/net/rtnetlink.h \
  include/net/netlink.h \
  include/net/inet_ecn.h \
  include/linux/ip.h \
  include/uapi/linux/ip.h \
  include/net/inet_sock.h \
    $(wildcard include/config/inet.h) \
  include/net/sock.h \
    $(wildcard include/config/net.h) \
  include/linux/uaccess.h \
  include/linux/page_counter.h \
  include/linux/memcontrol.h \
    $(wildcard include/config/memcg/swap.h) \
  include/linux/vmpressure.h \
  include/linux/eventfd.h \
    $(wildcard include/config/eventfd.h) \
  include/linux/writeback.h \
  include/linux/flex_proportions.h \
  include/linux/backing-dev-defs.h \
  include/linux/filter.h \
    $(wildcard include/config/bpf/jit.h) \
    $(wildcard include/config/have/ebpf/jit.h) \
  arch/arm64/include/asm/cacheflush.h \
  include/uapi/linux/filter.h \
  include/linux/rculist_nulls.h \
  include/linux/poll.h \
  include/uapi/linux/poll.h \
  arch/arm64/include/generated/asm/poll.h \
  include/uapi/asm-generic/poll.h \
  include/net/dst.h \
  include/net/neighbour.h \
  include/net/tcp_states.h \
  include/uapi/linux/net_tstamp.h \
  include/net/request_sock.h \
  include/net/netns/hash.h \
  include/net/l3mdev.h \
  include/net/fib_rules.h \
  include/uapi/linux/fib_rules.h \
  include/net/dsfield.h \
  include/linux/ipv6.h \
    $(wildcard include/config/ipv6/router/pref.h) \
    $(wildcard include/config/ipv6/route/info.h) \
    $(wildcard include/config/ipv6/optimistic/dad.h) \
    $(wildcard include/config/ipv6/mip6.h) \
    $(wildcard include/config/ipv6/subtrees.h) \
  include/uapi/linux/ipv6.h \
  include/linux/icmpv6.h \
  include/uapi/linux/icmpv6.h \
  include/linux/tcp.h \
    $(wildcard include/config/tcp/md5sig.h) \
  include/linux/win_minmax.h \
  include/net/inet_connection_sock.h \
  include/net/inet_timewait_sock.h \
  include/net/timewait_sock.h \
  include/uapi/linux/tcp.h \
  include/linux/udp.h \
  include/uapi/linux/udp.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_msg_tx.h \
    $(wildcard include/config/rwnx/p2p/debugfs.h) \
    $(wildcard include/config/rwnx/fullmac.h) \
    $(wildcard include/config/rwnx/bfmer.h) \
    $(wildcard include/config/rwnx/mumimo/tx.h) \
    $(wildcard include/config/rftest.h) \
    $(wildcard include/config/mcu/message.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_defs.h \
    $(wildcard include/config/br/support.h) \
    $(wildcard include/config/vht/for/old/kernel.h) \
    $(wildcard include/config/he/for/old/kernel.h) \
    $(wildcard include/config/rwnx/split/tx/buf.h) \
    $(wildcard include/config/sched/scan.h) \
    $(wildcard include/config/prealloc/txq.h) \
  include/linux/dmapool.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_mod_params.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_debugfs.h \
    $(wildcard include/config/rwnx/debugfs.h) \
    $(wildcard include/config/rwnx/fhost.h) \
    $(wildcard include/config/dur.h) \
  include/generated/uapi/linux/version.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_fw_trace.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_tx.h \
    $(wildcard include/config/rwnx/amsdus/tx.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/lmac_types.h \
    $(wildcard include/config/rwnx/tl4.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/ipc_shared.h \
    $(wildcard include/config/rwnx/agg/tx.h) \
    $(wildcard include/config/user/max.h) \
    $(wildcard include/config/rwnx/old/ipc.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/ipc_compat.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/lmac_mac.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_txq.h \
    $(wildcard include/config/mac80211/txq.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/hal_desc.h \
    $(wildcard include/config/trident.h) \
    $(wildcard include/config/elma.h) \
    $(wildcard include/config/karst.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_rx.h \
    $(wildcard include/config/rwnx/mon/data.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/aicwf_txrxif.h \
    $(wildcard include/config/prealloc/rx/skb.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/aicwf_rx_prealloc.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/aicwf_sdio.h \
    $(wildcard include/config/reg.h) \
    $(wildcard include/config/sdio/pwrctrl.h) \
    $(wildcard include/config/oob.h) \
    $(wildcard include/config/platform/amlogic.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_cmds.h \
    $(wildcard include/config/rwnx/sdm.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/lmac_msg.h \
    $(wildcard include/config/req.h) \
    $(wildcard include/config/cfm.h) \
    $(wildcard include/config/monitor/req.h) \
    $(wildcard include/config/monitor/cfm.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_radar.h \
    $(wildcard include/config/rwnx/radar.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_utils.h \
    $(wildcard include/config/rwnx/dbg.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/aicwf_debug.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_mu_group.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_platform.h \
    $(wildcard include/config/fw/name.h) \
    $(wildcard include/config/trd/name.h) \
    $(wildcard include/config/karst/name.h) \
  include/linux/pci.h \
    $(wildcard include/config/pci/iov.h) \
    $(wildcard include/config/pcieaer.h) \
    $(wildcard include/config/pcieaspm.h) \
    $(wildcard include/config/pcie/ptm.h) \
    $(wildcard include/config/pci/msi.h) \
    $(wildcard include/config/pci/ats.h) \
    $(wildcard include/config/pci/domains/generic.h) \
    $(wildcard include/config/pci/bus/addr/t/64bit.h) \
    $(wildcard include/config/arch/sun50iw6.h) \
    $(wildcard include/config/pcieportbus.h) \
    $(wildcard include/config/pcie/ecrc.h) \
    $(wildcard include/config/ht/irq.h) \
    $(wildcard include/config/pci/domains.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/pci/quirks.h) \
    $(wildcard include/config/hibernate/callbacks.h) \
    $(wildcard include/config/pci/mmconfig.h) \
    $(wildcard include/config/acpi/mcfg.h) \
    $(wildcard include/config/hotplug/pci.h) \
    $(wildcard include/config/eeh.h) \
  include/linux/io.h \
  include/linux/resource_ext.h \
  include/uapi/linux/pci.h \
  include/uapi/linux/pci_regs.h \
  include/linux/pci_ids.h \
  arch/arm64/include/asm/pci.h \
  include/linux/pci-dma-compat.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_gki.h \
    $(wildcard include/config/gki/opt/features.h) \
    $(wildcard include/config/android.h) \
  net/wireless/core.h \
    $(wildcard include/config/cfg80211/developer/warnings.h) \
  include/linux/rfkill.h \
    $(wildcard include/config/rfkill.h) \
    $(wildcard include/config/rfkill/leds.h) \
  include/uapi/linux/rfkill.h \
  include/linux/leds.h \
    $(wildcard include/config/leds/triggers.h) \
    $(wildcard include/config/leds/trigger/disk.h) \
    $(wildcard include/config/leds/trigger/mtd.h) \
    $(wildcard include/config/leds/trigger/camera.h) \
    $(wildcard include/config/new/leds.h) \
    $(wildcard include/config/leds/trigger/cpu.h) \
  include/net/genetlink.h \
  include/linux/genetlink.h \
  include/uapi/linux/genetlink.h \
  net/wireless/reg.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_compat.h \
    $(wildcard include/config/vendor/rwnx.h) \
    $(wildcard include/config/vendor/rwnx/amsdus/tx.h) \
  include/linux/bitfield.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/sdio_host.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_dini.h \
  drivers/net/wireless/aic8800/aic8800_fdrv/reg_access.h \
    $(wildcard include/config/addr.h) \

drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.o: $(deps_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.o)

$(deps_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_testmode.o):
