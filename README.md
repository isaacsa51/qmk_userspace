# Splitkb QMK Userspace

This is the splitkb userspace repository which allows for an external set of QMK keymaps with halcyon modules to be defined and compiled. This is useful for users who want to maintain their own keymaps without having to fork the splitkb QMK or vial repository.

If you want to compile firmware without any modules you can also use the [main qmk_userspace repo](https://github.com/qmk/qmk_userspace).

If the keyboard has not been merged yet to the main branch of QMK you may need to edit the workflow, for that see [Extra info](#extra-info)

## Howto configure your build targets

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. If you have already forked the `qmk/qmk_userspace` repository before you can add this repository manually following the [steps below](#adding-splitkb-fork-to-an-existing-fork).
1. Clone your fork to your local machine
1. Enable userspace in QMK config using `qmk config user.overlay_dir="$(realpath qmk_userspace)"`
1. Add a new keymap for your board by copy, pasting and renaming the `default_hlc` keymap within the `keyboards/splitkb/halcyon/$KB$/keymaps` folder.
1. You may want to replace the `qmk.json` with the empty `qmk_empty.json` if you want to start from scratch as it will otherwise compile all default options.
1. Add your keymap(s) to the build by running `qmk userspace-add -kb <your_keyboard> -km <your_keymap> -e <halcyon_module>=1 -e TARGET=<filename>`.
    * This will automatically update your `qmk.json` file
    * Corresponding `qmk userspace-remove -kb <your_keyboard> -km <your_keymap> -e <halcyon_module>=1 -e TARGET=<filename>`.
    * Listing the build targets can be done with with `qmk userspace-list`
    * If you want to use a module:
        * For the filename make it so you can differentiate between the different firmwares for the modules. `kyria_rev4_default_encoder` for example.
        * The following options are available for the halcyon modules:
            * HLC_NONE, If you don't have a module installed but you do have a module on the other half.
            * HLC_ENCODER, If you have an encoder module installed.
            * HLC_TFT_DISPLAY, If you have a tft rgb display installed.
            * HLC_CIRQUE_TRACKPAD, If you have a Cirque trackpad installed.
1. Commit your changes


## Howto build with GitHub

1. In the GitHub Actions tab, enable workflows
1. Push your changes above to your forked GitHub repository
1. Look at the GitHub Actions for a new actions run
1. Wait for the actions run to complete
1. Inspect the Releases tab on your repository for the latest firmware build


## Howto build locally

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. `cd` into this repository's clone directory
1. Set global userspace path: `qmk config user.overlay_dir="$(realpath .)"` -- you MUST be located in the cloned userspace location for this to work correctly
    * This will be automatically detected if you've `cd`ed into your userspace repository, but the above makes your userspace available regardless of your shell location.
1. Compile normally: `qmk compile -kb your_keyboard -km your_keymap -e <your_module>=1 -e TARGET=<filename>` or `make your_keyboard:your_keymap -e <your_module>=1 -e TARGET=<filename>`

Alternatively, if you configured your build targets above, you can use `qmk userspace-compile` to build all of your userspace targets at once.


## Extra info

If you wish to point GitHub actions to a different repository, a different branch, or even a different keymap name, you can modify `.github/workflows/build_binaries.yml` to suit your needs.

To override the `build` job, you can change the following parameters to use a different QMK repository or branch, this can be useful if you want to use a the main QMK repository or a different vial branch. For example:
```
    with:
      qmk_repo: qmk/qmk_firmware
      qmk_ref: master
```
Our halcyon module code should work fine with the main QMK repository but it may break if there are any breaking changes from QMK in the future. We will try our best to keep this repository up-to-date.

If you wish to manually manage `qmk_firmware` using git within the userspace repository, you can add `qmk_firmware` as a submodule in the userspace directory instead. GitHub Actions will automatically use the submodule at the pinned revision if it exists, otherwise it will use the default latest revision of `qmk_firmware` from the main repository. This will not work when using vial.

This can also be used to control which fork is used.

1. (First time only) `git submodule add https://github.com/qmk/qmk_firmware.git`
1. (To update) `git submodule update --init --recursive`
1. Commit your changes to your userspace repository


## Adding splitkb fork to an existing fork

### New branch

If you have already forked the qmk/qmk_userspace repository before you may need to manually add the `halcyon` branch.

1. Add a new upstream `git remote add upstream https://github.com/splitkb/qmk_userspace.git`
1. Fetch the upstream `git fetch upstream`
1. Create a new branch based on the upstream `git checkout -b halcyon upstream/halcyon`
1. Make any changes you want and push it to github `git push -u origin halcyon`

### Existing branch

You may also want to just add the files to your own branch if you have already setup a custom userspace before.

1. Clone or download the files from our fork or add it as a new branch as above.
1. Copy over the contents of `users/halcyon_modules/rules.mk` and the `users/halcyon_modules/splitkb/` folder to your personal user folder.

If you want to modify an existing keymap (from the original Kyria, Elora or an Aurora board for example). Make sure to add 10 new keys in your keymap (Look at `keyboards/splitkb/halcyon/kyria/keymaps/default_hlc` for an example).

Do note that we use some quantum functions in our userspace so there may be a conflict when compiling. If you use the `_user` functions you should be fine.
